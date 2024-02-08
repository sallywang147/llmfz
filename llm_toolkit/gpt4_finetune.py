from openai import OpenAI
client = OpenAI()

#commented code is for finetuning dataset generation

client.files.create(
  file=open("../train_data/formatted_gpt4.jsonl", "rb"),
  purpose="fine-tune"
)


client.files.create(
  file=open("../train_data/onestep.json", "rb"),
  purpose="fine-tune"
)


client.fine_tuning.jobs.create(
  training_file="file-PrWIBHtsHoguSVtOMYdzVe26", 
  model="davinci-002", 
  hyperparameters={
    "n_epochs":5
  }  
)

print(client.fine_tuning.jobs.list(limit=10))
