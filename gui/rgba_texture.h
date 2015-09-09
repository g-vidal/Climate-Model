#ifndef RGBA_TEXTURE_H
#define RGBA_TEXTURE_H

#include <assert.h>

class RGBATexture
{
    public:
    unsigned char* data;
    int width;
    int height;
    unsigned int id;
    bool mipmap;
    bool has_material;
    float specular[4];
    float diffuse[4];
    float ambient[4];
    float shininess[1];
    bool has_emission;
    float emission[4];
    RGBATexture()
    {
	data=0;
	id=0;
	mipmap=false;
	has_material=0;
	has_emission=0;
    }
    ~RGBATexture()
    {
	delete[] data;
    }
    void set_material(float* spec,float* diff,float* ambi,float shin)
    {
	for (int i=0;i<=3;i++) specular[i]=spec[i];
	for (int i=0;i<=3;i++) diffuse[i]=diff[i];
	for (int i=0;i<=3;i++) ambient[i]=ambi[i];
	*shininess=shin;
	has_material=1;
    }
    void set_emission(float* emi)
    {
	for (int i=0;i<=3;i++) emission[i]=emi[i];
	has_emission=1;
    }
	
    void gl_init(const char* file,int w,int h,int patate=0)
    {
	assert(data==0);
	mipmap=patate;
	data = new unsigned char[w*h*4];
	width=w;
	height=h;
	FILE* fil = fopen(file,"rb");
	fread(data,w*h,4,fil);
	fclose(fil);
	
	glGenTextures(1,&id); 	//Génère un n° de texture
	gl_define();
    }
    void gl_define()
    {
	glBindTexture(GL_TEXTURE_2D,id); 	//Sélectionne ce n°
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
#ifndef PATATE
	if (mipmap)
	{
#endif
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4 , width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
#ifndef PATATE
	}
	else
	{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D (GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
#endif
    }
    void gl_bind()
    {
	glBindTexture(GL_TEXTURE_2D,id); 	//Sélectionne ce n°
	if (has_material)
	{ 
	    glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
	    glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse);
	    glMaterialfv(GL_FRONT,GL_AMBIENT,ambient);
	    glMaterialfv(GL_FRONT,GL_SHININESS,shininess);
	}
	if (has_emission)
	{
	    glMaterialfv(GL_FRONT,GL_EMISSION,emission);
	}
    }	

};

#endif //RGBA_TEXTURE_H
