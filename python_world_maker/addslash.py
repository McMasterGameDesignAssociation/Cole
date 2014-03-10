
def getFileContents(fname):
    file_in = open(fname, 'r')
    contents = file_in.read()
    contents = contents.split('\n')
    file_in.close()
    return contents

def addSeperator(seperatorChar, contents):
    newList = []
    rowList = []
    for i in range(len(contents)):
        for j in range(len(contents[0])):
            rowList.append(contents[i][j] + seperatorChar)
        newList.append(rowList)
        rowList = []
    return newList

def writeToFile(fname, contents):
    file_out = open(fname, 'w')
    temp = ""
    for i in range(len(contents)):
        for j in range(len(contents[0])):
            temp += contents[i][j]
        if (i != len(contents) -1):        
            temp +="\n"
        else:
            temp += "\n*"
        file_out.write(temp)
        temp = ""

def removeComments(contents):
    list = []
    for i in range(len(contents)):
        if (contents[i][0] == "/" and contents[i][1] == "/"):
            continue     
        list.append(contents[i])
    return list
                     
def main():
    fname_in  = raw_input("In File Name: ")
    fname_out = raw_input("Out File Name: ")
    contents = getFileContents(fname_in)
    contents = removeComments(contents)
    newList = addSeperator('/', contents)
    writeToFile(fname_out, newList)
    print "Working..."
    print "...."
    print "...."
    print "...."
    print "...."
    print "...."
    print "...."
    print "...."
    print "File Created!"
main()
    
    

    
    
