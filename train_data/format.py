def reformat(file): 
        data = open(f"./{file}", "r")
        formatted_data = open(f"./formatted_{file}", "a+")
        for line in data:
                if "prompt" in line:
                        formatted_data.write("{"+line.strip())
                if "completion" in line:
                        formatted_data.write(line.strip()+"}\n") 

def main():
        reformat("gpt4.jsonl")
        reformat("working_gpt4.json")
if __name__ == "__main__":
       main()  