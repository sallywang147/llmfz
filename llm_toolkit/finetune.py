import os
import argparse
import random
import torch
import transformers
from datasets import Dataset
from transformers import (
    AutoModelForCausalLM, 
    AutoTokenizer,
    default_data_collator, 
    Trainer, 
    TrainingArguments,
    TrainerCallback,
)
from peft import prepare_model_for_int8_training, LoraConfig, get_peft_model, PeftModel


def maybe_load_models(model=None, tokenizer=None):

    if model is None:
        model = AutoModelForCausalLM.from_pretrained(
            "codellama/CodeLlama-7b-hf",
            load_in_8bit=True,
            torch_dtype=torch.float16,
            device_map= "auto",
        )

    if tokenizer is None:
        tokenizer = AutoTokenizer.from_pretrained(
            "codellama/CodeLlama-7b-hf",
        )

     model = AutoModelForCausalLM.from_pretrained(
            model,
            load_in_8bit=True,
            torch_dtype=torch.float16,
            device_map= "auto",
        )
     tokenizer =  AutoTokenizer.from_pretrained(
            tokenizer
        )


def reset_models():
    global model
    global tokenizer

    del model
    del tokenizer

    model = None
    tokenizer = None


def tokenize_and_train(
    model=None,
    tokenizer=None, 
    training_data,
    max_seq_length,
    micro_batch_size,
    gradient_accumulation_steps,
    epochs,
    learning_rate,
    lora_r,
    lora_alpha,
    lora_dropout,
    model_name):
    reset_models()
    maybe_load_models(model, tokenizer)
    tokenizer.pad_token_id = 0
    samples = training_data.split("<end of text>")
    print("Number of samples: " + str(len(samples)))
        
    def tokenize(item):
        result = tokenizer(
            item["text"],
            truncation=True,
            max_length=max_seq_length,
            padding="max_length",
        )
        return {
            "input_ids": result["input_ids"][:-1],
            "attention_mask": result["attention_mask"][:-1],
        }

    def to_dict(text):
        return {"text": text}

    samples = [to_dict(x) for x in samples]
    data = Dataset.from_list(samples)            
    data = data.shuffle().map(lambda x: tokenize(x))

    model = prepare_model_for_int8_training(model)

    model = get_peft_model(model, LoraConfig(
        r=lora_r,
        lora_alpha=lora_alpha,
        target_modules=["q_proj", "v_proj"],
        lora_dropout=lora_dropout,
        bias="none",
        task_type="CAUSAL_LM",
    ))
    output_dir = f"./lora-{model_name}"
    #we may or may not need the line below, depending on the device
    #model = model.to(torch.device('cuda'))
    print("Training...")

    training_args = transformers.TrainingArguments(
        # Set the batch size for training on each device (GPU, CPU, or TPU).
        per_device_train_batch_size=micro_batch_size, 

        # Number of steps for gradient accumulation. This is useful when the total 
        # batch size is too large to fit in GPU memory. The effective batch size 
        # will be the product of 'per_device_train_batch_size' and 'gradient_accumulation_steps'.
        gradient_accumulation_steps=gradient_accumulation_steps,  

        # Number of warmup steps for the learning rate scheduler. During these steps, 
        # the learning rate increases linearly from 0 to its initial value. Warmup helps
        #  to reduce the risk of very large gradients at the beginning of training, 
        # which could destabilize the model.
        # warmup_steps=100, 

        # The total number of training steps. The training process will end once this 
        # number is reached, even if not all the training epochs are completed.
        # max_steps=1500, 

        # The total number of epochs (complete passes through the training data) 
        # to perform during the training process.
        num_train_epochs=epochs,  

        # The initial learning rate to be used during training.
        learning_rate=learning_rate, 

        # Enables mixed precision training using 16-bit floating point numbers (FP16). 
        # This can speed up training and reduce GPU memory consumption without 
        # sacrificing too much model accuracy.
        fp16=True,  

        # The frequency (in terms of steps) of logging training metrics and statistics 
        # like loss, learning rate, etc. In this case, it logs after every 20 steps.
        logging_steps=20, 

        # The output directory where the trained model, checkpoints, 
        # and other training artifacts will be saved.
        output_dir=output_dir, 

        # The maximum number of checkpoints to keep. When this limit is reached, 
        # the oldest checkpoint will be deleted to save a new one. In this case, 
        # a maximum of 3 checkpoints will be kept.
        save_total_limit=100,  
    )


    trainer = transformers.Trainer(
        # The pre-trained model that you want to fine-tune or train from scratch. 
        # 'model' should be an instance of a Hugging Face Transformer model, such as BERT, GPT-2, T5, etc.
        model=model, 

        # The dataset to be used for training. 'data' should be a PyTorch Dataset or 
        # a compatible format, containing the input samples and labels or masks (if required).
        train_dataset=data, 

        # The TrainingArguments instance created earlier, which contains various 
        # hyperparameters and configurations for the training process.
        args=training_args, 

        # A callable that takes a batch of samples and returns a batch of inputs for the model. 
        # This is used to prepare the input samples for training by batching, padding, and possibly masking.
        data_collator=transformers.DataCollatorForLanguageModeling( 
            tokenizer,  
            # Whether to use masked language modeling (MLM) during training. 
            # MLM is a training technique used in models like BERT, where some tokens in the 
            # input are replaced by a mask token, and the model tries to predict the 
            # original tokens. In this case, MLM is set to False, indicating that it will not be used.
            mlm=False, 
        ),
    )

    result = trainer.train(resume_from_checkpoint=False)

    model.save_pretrained(output_dir)
    
    reset_models()

    return result


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--train_file", type=str,
                        help="providing training data file.")
    parser.add_argument("--model_name", action=str,
                        help="name of the trained peft model.")

    args = parser.parse_args()
    train_file = = open(args.train_file, "r")
    train_data = train_file.read() 
    result = tokenize_and_train(train_data,
        max_seq_length=4096,
        micro_batch_size=1,
        gradient_accumulation_steps=16,
        epochs=5,
        learning_rate=2e-5,
        lora_r=8,
        lora_alpha=32,
        lora_dropout=0.1,
        model_name=args.model_name)
    print(f"train result: {result}\n")


 #lora hyperparameters from this paper: https://github.com/microsoft/LoRA/tree/main/examples/NLG      
if __name__ == "__main__":  
       sys.exit(main())