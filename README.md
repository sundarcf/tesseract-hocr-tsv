Tesseract-hocr-tsv
==================

Provides interface for obtaining hocr data in tsv format.


First, compile <code>get_lines_and_words.cpp</code> file:
<code>g++ -Wall get_lines_and_words.cpp -ltesseract -llept -o get_lines_and_words</code>

Run server:
<code>rails s </code>

Browse to the root of the app. 
On the file upload form, upload an image. 
The app will perform ocr and return output with hocr data. 
Data will be downloaded as a tsv file.
