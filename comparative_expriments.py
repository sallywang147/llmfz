import os
import sys
import subprocess

selected_benchmarks = ["zlib.yaml", 
                        "libxls.yaml", 
                        "libpcap.yaml", 
                        "open62541.yaml", 
                        "libpng.yaml", 
                        "openssl.yaml", 
                        "vorbis.yaml", 
                        "wolf2.yaml", 
                        "stb.yaml", 
                        "freetype2.yaml"]

def run_finetuned_model(benchmark):
    benchmark_path = os.path.join("./benchmark-sets/all/", benchmark)
    results_dir = f"{benchmark}_finetune_results"
    if not os.path.isdir(results_dir):
        os.mkdir(results_dir)
    subprocess.call(["python3.11", "./run_all_experiments.py", \
     "--model=ftpeft_llama", "-y", str(benchmark_path), f"--work-dir={ results_dir}"])


def run_raw_model(benchmark):
    benchmark_path = os.path.join("./benchmark-sets/all/", benchmark)
    results_dir = f"{benchmark}_peft_results"
    if not os.path.isdir(results_dir):
        os.mkdir(results_dir)
    subprocess.call(["python3.11", "./run_all_experiments.py", \
     "--model=peft_llama", "-y", str(benchmark_path), f"--work-dir={ results_dir}"])


def main():

    for b in selected_benchmarks: 
        run_raw_model(b)
        run_finetuned_model(b)


if __name__ == "__main__":
    main()    