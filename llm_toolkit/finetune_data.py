import io
import os
import xlrd
import pandas as pd
import fnmatch
import simplejson as json
from collections import OrderedDict
from numpy import random
from numpy import random
from glob import iglob

def find_function(file, first, last):
    try:
        start = file.rindex(first) + len(first)
        end = file.rindex(last, start)
        return file[start:end]
    except ValueError:
        return ""


directory = '/home/sallyjunsongwang/llmfz/comparative_results_gpt4'


for (root, directories, files) in os.walk(directory, topdown=False):
        for name in files:
                if name == "prompt.txt":
                        prompt_file = os.path.join(root, name)
                        with open(prompt_file, "r") as file:
                                file =  file.read()
                                first = '<function header>'
                                last = '</function header>'
                                function = find_function(file, first, last)
                                print(f"This is the function signature:  {function}\n")
        for name in directories:
                if name == "fixed_targets": 
                        targets_dir = os.path.join(root, name)
                        print(f"target file: {targets_dir}\n")
                        for target in os.listdir(targets_dir):
                                possible_target = os.path.join(targets_dir, target)
                                if os.path.isfile(possible_target):
                                        with open(possible_target, "r") as target_file:
                                                tf = target_file.read()
                                                print(f"target file : {tf}\n")
         
'''
with open("/home/sallyjunsongwang/llmfz/comparative_results_gpt4/output-avahi-avahi_dns_packet_append_record/prompt.txt", "r") as file:
        #print(file.read().replace('\\n','\n'))
        
        for line in file.read().split('\\n'):
                print(line)
                print('\n')
        
        test_str =  file.read()
        print(test_str)
        print('\n')
        # initializing substrings
        sub1 = '<function header>'
        sub2 = '</function header>'
    
        # getting index of substrings
        res = find_between_r(test_str, sub1, sub2)

        # printing result
        print("The extracted string : " + res)

#def contextualized_data_prep(prompt, target):

#def main():

#if __name__ == "__main__":
#       main()    
'''