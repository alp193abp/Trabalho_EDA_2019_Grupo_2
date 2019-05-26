import string as st
import re

def word_id(dictionary):
    dict2={}
    for Id in dictionary.keys():
        texto1 = dictionary[Id][0]+' '+dictionary[Id][1]
        texto2 = texto1.split()
        texto3 = [x.strip(st.punctuation).lower() for x in texto2]
        words = list(set(texto3))
    
        for word in words:
            if word in dict2.keys():
                dict2[word].append(Id)
            else:
                dict2[word]=[Id]
                
    if '' in dict2.keys():
        dict2.pop('')
            
    return dict2