import requests
from bs4 import BeautifulSoup
import sys

mem = requests.get("https://www.azlyrics.com/lyrics/"+sys.argv[1]+"/"+sys.argv[2]+".html")

soup = BeautifulSoup(mem.text, "html.parser")

soup = soup.find_all('div')[11]

soup = soup.find_all('div')[9]

print (soup.get_text())
