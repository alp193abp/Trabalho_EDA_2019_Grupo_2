def word_id(dictionary):
    dict2={}
    dict3={}
    for Id in dictionary.keys():
        texto1 = dictionary[Id][0]+' '+dictionary[Id][1]
        texto2 = texto1.split()
        texto3 = []
        for i in texto2:
            texto3.extend(i.split('--'))
        texto4 = [x.strip(st.punctuation).lower() for x in texto3]
        words = list(set(texto4))
        if '' in words:
            words.pop(words.index(''))
        dict2[Id]=words
    
        for word in words:
            if word in dict3.keys():
                dict3[word].append(Id)
            else:
                dict3[word]=[Id]
            
    return dict3