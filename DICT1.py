import string as st
import re
import _pickle as cPickle

def id_texts(archiv):
    list_id = re.findall('<doc id="\d+"',archiv)
    list_text =[]
    dic_texts = {}
    for i in list_id:
        id_original=i[9:len(i)-1]
        
        start_doc = archiv.find(i)
        end_doc = archiv[start_doc:len(archiv)].find('ENDOFARTICLE')+start_doc
        doc=archiv[start_doc:end_doc]
        
        start_title=doc.find('title=')+7
        end_title=doc.find('nonfiltered=')-2
        title=doc[start_title:end_title]
        
        start_text=doc.find('">')+3
        end_text=len(doc)
        text=doc[start_text:end_text]
        
        list_text.append([id_original,[title,text]])
        
    list_text.sort(key=lambda x: x[1])
    
    for j in range(len(list_text)):
        dic_texts[j]=list_text[1]
    
    return dic_texts