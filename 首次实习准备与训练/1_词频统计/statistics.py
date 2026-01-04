import jieba
f=open("八十天环游地球.txt",encoding='utf-8')   #读取源文件
fi=open("八十天环游地球-章节.txt",'w',encoding='utf-8') #打开新文件
for i in f: #遍历文本每一行
    text=i.split()[0]
    if text[0]=="第" and text[-1]=='章':
    #取出第一段文本，如果首字符是第&尾字符是章，代表是章节
        fi.write("{}\n".format(i.replace('\n',''))) #格式化保存
fi.close()
f.close()

f1=open("八十天环游地球.txt",'r',encoding="utf-8")
ls=f1.read().split('□ 作者：儒勒·凡尔纳')   
#划分每一个章节组成一个列表为ls
f1.close()
ls1=[]  #ls1是存储每一个章节出现最多的词语及其次数
for i in range(len(ls)-1):
    d={}    #字典d用于对词语进行计数
    lt=jieba.lcut(ls[i])    
    #对每一个章节内容进行分词，组成列表lt
    for word in lt:
        if len(word)>=2:    #进行计数的词语长度不少于2个字符
            d[word]=d.get(word,0)+1
    items=list(d.items())   #将字典d转化成列表items
    items.sort(key=lambda x:x[1],reverse=True)
    #对由元组组成的列表items进行词语出现次数的降序排序
    ls1.append(items[0])
f2=open('八十天环游地球-章节.txt','r',encoding='utf-8')
ls2=[]
for line in f2.readlines():
    ls2.append(line.strip('\n').split()[0])
    #ls2列表存储"第x章"
for j in range(len(ls2)):
    print("{:<14} {:<8} {:<8}".format(ls2[j],ls1[j][0],ls1[j][1]))
    #输出第*章  出现次数最多的词语  这个词语的出现次数
f2.close()
#接下来将每章节最高频词语写入文件中
f3=open("章节高频词统计.txt",'w',encoding='utf-8')
for j in range(len(ls2)):
    f3.write("{:<14} {:<8} {:<8}\n".format(ls2[j],ls1[j][0],ls1[j][1]))
    #format进行格式化控制
f3.close() 
