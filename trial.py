import os
import sys
import argparse
import json
import random
import torch
import transformers
from datasets import Dataset, load_dataset
from accelerate import dispatch_model, infer_auto_device_map
from accelerate.utils import get_balanced_memory
from torch.cuda.amp import autocast
from transformers import (
    LlamaForCausalLM,
    LlamaTokenizer,
    GenerationConfig,
    BitsAndBytesConfig,
    AutoTokenizer,
    AutoModelForCausalLM,
    TrainingArguments,
    Trainer,
    DataCollatorForSeq2Seq,
)
from peft import (
    prepare_model_for_int8_training,
    LoraConfig,
    PeftConfig,
    get_peft_model,
    PeftModel,
    get_peft_model_state_dict,
    set_peft_model_state_dict,
)

harfbuzz_sigs = ["struct hb_face_t * hb_subset_preprocess(struct hb_face_t * source)",
                 "void hb_ot_shape_glyphs_closure(struct hb_font_t * font, struct hb_buffer_t * buffer, struct hb_feature_t * features, int num_features, struct hb_set_t * glyphs)",
                 "int hb_shape_justify(struct hb_font_t * font, struct hb_buffer_t * buffer, struct hb_glyph_extents_t * features, int num_features, char ** shaper_list, float min_target_advance, float max_target_advance, float * advance, int * var_tag, float * var_value)",
                 "double solve_itp<hb_shape_justify::$_3>(anon * f, double a, double b, double epsilon, double min_y, double max_y, double * ya, double * yb, double * y)",
                 "double hb_shape_justify::$_3::operator(anon * this, double x)",
                 ]

def generate_text(prompt):
  peft_model_id = "sallywww/LLaMA_oneStep_fuzzTragets"
  config = LoraConfig.from_pretrained(peft_model_id)
  raw_model = LlamaForCausalLM.from_pretrained(config.base_model_name_or_path)
  model = PeftModel.from_pretrained(raw_model, peft_model_id)
  tokenizer = LlamaTokenizer.from_pretrained(config.base_model_name_or_path)
  inputs = tokenizer(prompt, return_tensors="pt")
      #input_ids = inputs["input_ids"].to(model.device)
  with torch.no_grad():
      outputs = model.generate(input_ids=inputs["input_ids"].cuda(), \
                  generation_config=config)
      output_text = tokenizer.batch_decode(outputs.detach().cpu().numpy(), skip_special_tokens=True)[0]
  return output_text


def generate_and_tokenize_prompt(func_signature):
    full_prompt =f"""You are a security testing engineer who wants to write a C++ program to execute all lines in a given function by defining and initializing its parameters in a suitable way before fuzzing the function through <code>LLVMFuzzerTestOneInput</code>.
    Carefully study the function signature and its parameters, then generate a fuzz targets by the following instructions. YOU MUST call the function to fuzz in the solution.
    Try as many variations of possible inputs as possible. Do not use a random number generator such as <code>rand()</code>.
    Your goal is to write a fuzzing harness for the provided function header using <code>LLVMFuzzerTestOneInput</code>.
    All variables used MUST be declared and initialized. Carefully make sure that the variable and argument types in your code match and compiles successfully. Add type casts to make types match.
    Do not create new variables with the same names as existing variables. If you write code using <code>goto</code>, you MUST MUST also declare all variables BEFORE the <code>goto</code>. Never introduce new variables after the <code>goto</code>.
    It is important that the provided solution compiles and actually calls the function specified by the function signature:

    ### Input:
    {func_signature}
    """
    return full_prompt

def main():
    if os.path.isdir("../llmfz/finetuned_results") is False:
        os.mkdir("../llmfz/finetuned_results")
    if os.path.isdir("../llmfz/finetuned_results/output_harfbuzz") is False:
        os.mkdir("../llmfz/finetuned_results/output_harfbuzz")
    harfbuzz_count = 1
    for i in harfbuzz_sigs:
        raw_target = open(f"../llmfz/finetuned_results/output_harfbuzz/0{harfbuzz_count}.rawoutput", "w+")
        prompt = generate_and_tokenize_prompt(i)
        generated_target = generate_text(prompt)
        raw_target.write(generated_target)
        print(generated_target)
        raw_target.close()
        harfbuzz_count += 1


if __name__ == '__main__':
  sys.exit(main())