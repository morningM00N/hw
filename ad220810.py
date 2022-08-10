from pydoc import doc
import random

seedVal = 5695
random.seed(0)
def generateInput():
    global seedVal
    print(f"seed:{seedVal}")
    random.seed(seedVal)
    size = random.randint(5,10)
    if seedVal == 5695:
        size = 6
    arr = []
    for i in range(size):
        arr.append(random.randint(1,64))

    seedVal = random.randint(0,100000)
    return arr


op = ['=','+','*','%']

def getNext(opArr):
    idx = 0
    while idx<len(opArr) and opArr[idx]==3:
        opArr[idx]=0
        idx+=1
    if idx<len(opArr):
        opArr[idx]+=1
    

def getSolution(arr):
    ret = 0
    opArr = [0] * (len(arr)-1)
    while True:
        if (0 in opArr) == True:
            #print(opArr)                                    
            computedValue = []
            curVal = arr[0]
            for i in range(len(opArr)):
                if opArr[i]==0:
                    computedValue.append(curVal)
                    curVal = arr[i+1]
                elif opArr[i]==1:
                    curVal += arr[i+1]
                elif opArr[i]==2:
                    curVal *= arr[i+1]
                elif opArr[i]==3:
                    curVal %= arr[i+1]
            computedValue.append(curVal)
            allSame = True
            for i in range(len(computedValue)):
                if computedValue[i]!=computedValue[0]:
                    allSame = False
                    break
            if allSame == True:
                # eqCount = 0
                # for i in opArr:
                #     if i == 0:
                #         eqCount+=1
                # if eqCount>0:
                #     printStr = ""
                #     for i in range(len(arr)-1):
                #         printStr+=f" {str(arr[i])} {op[opArr[i]]}"
                #     printStr+=f" {str(arr[-1])}"
                #     print(printStr)
                ret +=1

        getNext(opArr)
        if sum(opArr) == 0:
            break
    return ret

fInput=open("input.txt",'w')
fSol = open('sol.txt','w')

fInput.write('100\n')
for i in range(100):
    arr = generateInput()
    print(f"{i}:{arr}")
    sol = getSolution(arr)
    fInput.write(f"{len(arr)}\n")
    for j in arr:
        fInput.write(f"{j}\n")
    fSol.write(f"#{i+1} {sol}\n")
    
    
fInput.close()
fSol.close()

