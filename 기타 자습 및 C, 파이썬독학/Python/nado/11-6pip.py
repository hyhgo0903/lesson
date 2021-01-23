from bs4 import BeautifulSoup
soup = BeautifulSoup("<p>Some<b>bad<i>HTML")
print(soup.prettify())
# pypi.org
# pip install beautifulsoup4(밑 터미널에)
# pip list
# pip show beautifulsoup4
# pip install --upgrade beautifulsoup4
# pip uninstall beautifulsoup4