import string as st
import re
import time

def id_texts(archiv):
    list_id = re.findall('<doc id="\d+"',archiv)
    list_end = re.findall('</doc>',archiv)

    
    return (len(list_id),len(list_end))
