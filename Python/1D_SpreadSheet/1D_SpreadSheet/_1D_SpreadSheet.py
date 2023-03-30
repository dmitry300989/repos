import sys

def ReadData():
    data = []
    with open('data.txt') as f:
        data = f.readlines()
    return data

def main():
    data = ReadData()
    n = len(data)
    cells=[0]*n
    ind_cell=0
    aval_cells=[]
    list_act=[]
    refs_cells = {'$':[]}
    for line in data:
        operation, arg_1, arg_2 = line.split()
        print(operation,arg_1,arg_2,sep=' ')
        val1 = 0
        val2 = 0
        list_act.append([operation,arg_1,arg_2])
        if operation=="VALUE":
            if arg_1[0]!="$":
                if arg_1 != "_":
                    cells[ind_cell]=int(arg_1)
                    aval_cells.append([ind_cell,int(arg_1)])
            else:
                if arg_1 not in refs_cells:
                    refs_cells[arg_1] = []
                refs_cells[arg_1].append([ind_cell,1])
            if arg_2[0]!="$":
                if arg_2 != "_":
                    cells[ind_cell]=int(arg_2)
                    aval_cells.append([ind_cell,int(arg_2)])
            else:
                if arg_2 not in refs_cells:
                    refs_cells[arg_2] = []
                refs_cells[arg_2].append([ind_cell,2])
    
        if operation =="ADD":
            if arg_1[0]!='$' and arg_2[0]!='$':
                val1=int(arg_1)
                val2=int(arg_2)
                cells[ind_cell]=val1+val2
                aval_cells.append([ind_cell,cells[ind_cell]])
            else:
                if arg_1[0]=='$':
                    if arg_1 not in refs_cells:
                        refs_cells[arg_1] = []
                    refs_cells[arg_1].append([ind_cell,1])

                if arg_2[0]=="$":
                    if arg_2 not in refs_cells:
                        refs_cells[arg_2] = []
                    refs_cells[arg_2].append([ind_cell,2])

        if operation =="SUB":
            if arg_1[0]!='$' and arg_2[0]!='$':
                val1=int(arg_1)
                val2=int(arg_2)
                cells[ind_cell]=val1-val2
                aval_cells.append([ind_cell,cells[ind_cell]])
            else:
                if arg_1[0]=='$':
                    if arg_1 not in refs_cells:
                        refs_cells[arg_1] = []
                    refs_cells[arg_1].append([ind_cell,1])

                if arg_2[0]=="$":
                    if arg_2 not in refs_cells:
                        refs_cells[arg_2] = []
                    refs_cells[arg_2].append([ind_cell,2])

        if operation =="MULT":
            if arg_1[0]!='$' and arg_2[0]!='$':
                val1=int(arg_1)
                val2=int(arg_2)
                cells[ind_cell]=val1*val2
                aval_cells.append([ind_cell,cells[ind_cell]])
            else:
                if arg_1[0]=='$':
                    if arg_1 not in refs_cells:
                        refs_cells[arg_1] = []
                    refs_cells[arg_1].append([ind_cell,1])

                if arg_2[0]=="$":
                    if arg_2 not in refs_cells:
                        refs_cells[arg_2] = []
                    refs_cells[arg_2].append([ind_cell,2])
        ind_cell+=1

    for cell in aval_cells:
        key_str = "$" + str(cell[0])
        if key_str in refs_cells:
            for r_cell in refs_cells[key_str]:
                k = r_cell[0]
                l = r_cell[1]
                list_act[k][l] = cell[1]
                l = 1 if l == 2 else 2
                t = 0
                if type(list_act[k][l]) == str:
                    if list_act[k][l][0] != '$':
                        if list_act[k][0] == "VALUE":
                            aval_cells.append([k,cell[1]])
                        if list_act[k][0] == "SUB":
                            t = int(list_act[k][1]) - int(list_act[k][2])
                            aval_cells.append([k, t])
                        if list_act[k][0] == "ADD":
                            t = cell[1] + int(list_act[k][l])
                            aval_cells.append([k, t])
                        if list_act[k][0] == "MULT":
                            t = cell[1] * int(list_act[k][l])
                            aval_cells.append([k, t])
                        cells[k] = t
                else:
                    if list_act[k][0] == "VALUE":
                            aval_cells.append([k,cell[1]])
                    if list_act[k][0] == "SUB":
                        t = int(list_act[k][1]) - int(list_act[k][2])
                        aval_cells.append([k, t])
                    if list_act[k][0] == "ADD":
                        t = cell[1] + int(list_act[k][l])
                        aval_cells.append([k, t])
                    if list_act[k][0] == "MULT":
                        t = cell[1] * int(list_act[k][l])
                        aval_cells.append([k, t])
                    cells[k] = t
        
    for i in range(len(cells)):
        print(cells[i])

if __name__ == "__main__":
    main()