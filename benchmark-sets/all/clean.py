import os
import yaml

def searchStringInYaml(filename):
    with open(filename) as file:
        contents = file.read()
    with open(filename, 'r+') as f:       
        lines = f.readlines()
        f.seek(0)
        if "Retrieving human-written fuzz targets of lzo from local Docker build." in contents: 
                f.writelines(lines[1:])

def clean(dir):
        directory = os.fsencode(dir)  
        for file in os.listdir(directory):
                filename = os.fsdecode(file)
                if filename.endswith(".yaml"):
                        searchStringInYaml(filename)


if __name__ == '__main__':
        clean("./")



                