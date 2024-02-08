**Caution for users: this fine-tuning section is under active development and fine-tuning code has not been reviewed. It likely contains errors, ommissions, and hidden bugs.**

# Fine-tuning Datasets Generation
In the llm_toolkit directory, please run the following command:
`python finetune_data.py --results <results_dir>`

 `<results_dir>` is the directory, where prompting only results are obtained. Please see [user guide](https://github.com/sallywang147/llmfz/blob/main/USAGE.md) on
 how to obtain prompting only based results. 

 The script will prepare three types of datasets and store the datasets in  `<results_dir>`  in response to different models: 

 1. [contextualized dataset](https://github.com/sallywang147/llmfz/blob/main/train_data/context.txt) (a .txt file particularly suitable for PEFT finetuning):

```
This is function signature: <function header>
prompt.txt in <results_dir>
function fuzz target(s) are: <target_1> <target_2>...
<end of text>
```
The comparison benchmark generates 203 training samples for contextualized finetuning.

 2.[lightly contextualized datatset](https://github.com/sallywang147/llmfz/blob/main/train_data/gpt4.json)  (a .json file without contextual information, particularly suited for GPT-3.5 and T5 models):
 
 ```
{"prompt": "prompt.txt in <results_dir>",
"completion":  "<target_1> <target_2>..."
}
```

 3. [one-step dataset w/out contexts](https://github.com/sallywang147/llmfz/blob/main/train_data/onestep.json) (a .json file without contextual information, particularly suited for GPT-3.5 and T5 models):

 ```
{"prompt": "function signature_1",
"completion":  "<target_1> "
}
{"prompt": "function signature_2",
"completion":  "<target_2> "
}
{"prompt": "function signature_3",
"completion":  "<target_3> "
}
```
  
We develop 2 and 3 datasets to compare the effectiveness of different fine-tuning.

 # Parameter Efficient (PEFT) Fine-tuning 

Hardware: we recommend at least one A100 GPU for PEFT fine-tuning.

installation requirements: `pip install -r requirements.txt` in the llm_toolit folder. 

Expected training time: 2-5 hours per model for 5 epochs. 

finetuning scripts for codeLLaMA and Falcon: `python finetune.py --model_name <codellama> --train_file <../train_data/context.txt>` , where `<codellama>`
and `<../train_data/context.txt>` can be adapted based on user's system .

Warning: the `finetnune.py` file is actively updated daily (maybe multiple times). So better to wait until we release an official version. 

finetuning scripts for LLaMA: `python llama_finetune.py`

We plan to expand the finetuing pipeline to support mmore models 

 # GPT4 Fine-tuning 

Note: I actually don't recommend fine-tuning GPT4. It requires a very rigid dataset format, which the raw data might not satisfy. 

 GPT4 fine-tuning dataset has strict requirements. So it requires further processing to get the format right. See [dataset formatting](https://platform.openai.com/docs/guides/fine-tuning/preparing-your-dataset)

 1. After generating training data (assuming your results are stored in the `train_data` directory, run `python reformmat.py` to generate openAI supported dataset
 2. run `curl https://api.openai.com/v1/files -H "Authorization: Bearer $OPENAI_API_KEY"` in terminal to check training data is successfully uploaded and obtain data_id
 3. start fine-tunning job according to this [procedure](https://platform.openai.com/docs/guides/fine-tuning/create-a-fine-tuned-model)
 4. you are done!

 # Results

 ##contextualized fine-tuning 
 [deployed peft llama](https://huggingface.co/sallywww/llama_fuzz_targets)

 More evaluations to come...

