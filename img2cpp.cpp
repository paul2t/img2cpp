#include <cstdio>
#include <cstring>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

char* get_file_name(char* path, size_t path_len, int& len)
{
	char* image_name = path + path_len;
	char* image_end = image_name;
	while (image_name > path && *image_name != '\\' && *image_name != '/')
	{
		if (*image_name == '.')
			image_end = image_name;
		--image_name;
	}
	if (*image_name == '/' || *image_name == '\\')
		++image_name;
	len = (int)(image_end - image_name);
	return image_name;
}

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		printf("Usage: img2cpp SOURCE_IMAGE\n");
		return 1;
	}
	
	char* source = argv[1];

	int name_len = 0;
	char* image_name = get_file_name(source, strlen(source), name_len);

	int x, y, n;
	unsigned char *data = stbi_load(source, &x, &y, &n, 0);
	printf("static unsigned char %.*s[%d*%d*%d] =\n{\n", name_len, image_name, x, y, n);
	int i = 0;
	for (int yi = 0; yi < y; ++yi)
	{
		printf("\t");
		for (int xi = 0; xi < x; ++xi)
		{
			for (int ni = 0; ni < n; ++ni)
			{
				printf("0x%02x, ", data[i++]);
			}
			printf(" ");
		}
		printf("\n");
	}
	printf("};\n");
	stbi_image_free(data);

	return 0;
}
