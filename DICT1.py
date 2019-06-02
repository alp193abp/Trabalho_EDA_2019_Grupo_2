import string as st
import re
import time

def id_texts(archiv):
    t0=time.time()
    list_id = re.findall('<doc id="\d+"',archiv)
    print(len(list_id))
    list_end = re.findall('ENDOFARTICLE',archiv)
    print(len(list_end)
    print('Tempo inicial:'+str(time.time()-t0))
    list_text = []
    
    t1=time.time()
    for i in range(len(list_id)):
        j=list_id[i]
        k=list_end[i]
        id_original=j[9:len(j)-1]
        
        start_doc = archiv.find(j)
        end_doc = archiv[start_doc:len(archiv)].find('ENDOFARTICLE')+start_doc
        doc=archiv[start_doc:end_doc]
        
        start_title=doc.find('title=')+7
        end_title=doc.find('nonfiltered=')-2
        title=doc[start_title:end_title]
        
        start_text=doc.find('">')+3
        end_text=len(doc)
        text=doc[start_text:end_text]
        
        list_text.append([id_original,title,text])
        
    list_text.sort(key=lambda x: x[1])
    print('Tempo for:'+str(time.time()-t1))
    
    t2=time.time()
    while True:rep
        if list_text[0][1]=='' and list_text[0][2]=='':
            list_text.pop(0)
        else:
            break
    print('Tempo while:'+str(time.time()-t2))
    
    t3=time.time()
    dic_texts={i:[list_text[i][1],list_text[i][2]] for i in range(len(list_text))}
    print('Tempo dict:'+str(time.time()-t3))
    
    return dic_texts