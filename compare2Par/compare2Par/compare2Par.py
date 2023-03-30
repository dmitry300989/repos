import argparse
import pandas as pd
from tabulate import tabulate

def ReadArgs():
    parser = argparse.ArgumentParser() 
    parser.add_argument('file', type=argparse.FileType('r'), nargs='+')
    args = parser.parse_args()
    return args

def ReadFiles(args):
    listParamDict = {}
    for f in args.file:
        paramDict = {}
        for line in f:
            name, var = line.partition("=")[::2]
            if isinstance(var, (int, float)):
                paramDict[name.strip()] = float(var)
            else:
                paramDict[name.strip()] = var
        listParamDict[f.name] = paramDict
    return listParamDict

def WriteTabToFile(df):
    with open('table.txt', 'w') as f:
        f.write(tabulate(df, headers = 'keys', tablefmt = 'psql'))

def CreateDataFrame(args):
    cols = []
    cols.append("Parameter")
    for x in args.file:
        cols.append(x.name)
    df = pd.DataFrame(columns=cols)
    return df

def FillDataFrame(df, fileParamDict, args):
    for fileName, paramDict in fileParamDict.items():
        for paramName, val in paramDict.items():
            if paramName not in df['Parameter'].values.tolist():
                if paramName not in fileParamDict[args.file[0].name]:
                    df.loc[len(df.index)] = [paramName, "n/a" ,fileParamDict[args.file[1].name][paramName]]
                elif paramName not in fileParamDict[args.file[1].name]:
                    df.loc[len(df.index)] = [paramName, fileParamDict[args.file[0].name][paramName] ,"n/a"]
                else:
                    if fileParamDict[args.file[0].name][paramName] != fileParamDict[args.file[1].name][paramName]:
                        df.loc[len(df.index)] = [paramName, fileParamDict[args.file[0].name][paramName] ,fileParamDict[args.file[1].name][paramName]]
    return df

def main():
    args = ReadArgs()
    fileParamDict = ReadFiles(args)
    df = CreateDataFrame(args)
    df = FillDataFrame(df, fileParamDict, args)
    WriteTabToFile(df)

if __name__ == '__main__':
    main()