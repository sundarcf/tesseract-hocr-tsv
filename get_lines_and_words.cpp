#include <iostream>
#include <cstdio>

#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

using namespace std;

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		cerr << "Please provide input image filename as first argument." << endl;
		return -1;
	}
	char *filename = argv[1];
//	printf("File: %s\n", filename);

	// Open input image with leptonica library
	Pix *image = pixRead(filename);

	tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
	api->Init(NULL, "eng");
	api->SetImage(image);
	Boxa* boxes = api->GetComponentImages(tesseract::RIL_TEXTLINE, true, NULL, NULL);
	printf("i\tj\tx\ty\tw\th\tc\tt\n");
	for (int i = 0; i < boxes->n; i++)
	{
		int j = -1;
		BOX* box = boxaGetBox(boxes, i, L_CLONE);
		api->SetRectangle(box->x, box->y, box->w, box->h);
		char* ocrResult = api->GetUTF8Text();
		float line_conf = api->MeanTextConf();
		printf("%d\t%d\t%d\t%d\t%d\t%d\t%0.2f\t%s\n",
				i, j, box->x, box->y, box->w, box->h, line_conf, ocrResult);
		tesseract::ResultIterator* ri = api->GetIterator();
		tesseract::PageIteratorLevel level = tesseract::RIL_WORD;
		if (ri != 0)
		{
			j = 0;
			do
			{
				const char* word = ri->GetUTF8Text(level);
				float word_conf = ri->Confidence(level);
				int x1, y1, x2, y2;
				ri->BoundingBox(level, &x1, &y1, &x2, &y2);
				printf("%d\t%d\t%d\t%d\t%d\t%d\t%0.2f\t%s\n",
						i, j, x1, y1, (x2 - x1 + 1), (y2 - y1 + 1), word_conf, word);
				delete[] word;
				j++;
			} while (ri->Next(level));
		}
	}
}
