#include "TextureManager.h"


TextureManager::TextureManager() {
}


TextureManager::~TextureManager() {
}


// create with and without a graphic filehandler
//returns the id of the texture
GLuint
TextureManager::LoadandCreateTexture(const char* fname) {
    MyFiles MF; // create an instance MyFiles (but really you should have one somewhere ?)
    return LoadandCreateTexture(fname, &MF);
}


//returns the id of the texture
GLuint
TextureManager::LoadandCreateTexture(const char* fname, MyFiles* FH) {
    if(Totaltextures.find(fname) == Totaltextures.end()) {
        // we gotta make a new texture
        GLuint texture_id;
        int w=0, h=0;
        const char *cstr = &fname[0u]; // embarrasing side effect of the decision to use char.....
        char* image = FH->Load(cstr, &w, &h);
        if(w*h == 0) {
            printf("Unable to load texture:%s \n", cstr);
            exit(1);
        }
        printf("Texture info for %s :-\n", cstr);
        printf("# width   : %d\n", w);
        printf("# Height  : %d\n", h);
        printf("# comp    : %d\n", FH->comp);
        glGenTextures(1, &texture_id);
        glBindTexture(GL_TEXTURE_2D, texture_id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        if(FH->comp == 4) {// check if we had an alpha texture or a plane (strictly speaking any value not 3 is wrong)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        }
        else {
            if(FH->comp != 3) printf("Made a default non alpha texture, comp was :%d\n", FH->comp);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        }
        if(glGetError() != GL_NO_ERROR) {
            printf("Oh bugger:- Model texture creation error, but attempting to carry on.\n");
        }
        glBindTexture(GL_TEXTURE_2D, 0);
        free(image); // release the cpu memory once its been put in the GPU
        Totaltextures.insert(std::make_pair(fname, texture_id));
        return texture_id;
    }
    return Totaltextures[fname];
}


// textures need to be deleted here
// removes from Texture space by ID, and from the map, return false if not possible
bool
TextureManager::deleteTexture(GLuint IDofTexture) {
    glDeleteTextures(1, &IDofTexture);
    //    std::map<std::string, GLuint>::iterator it;
    //    for(it=Totaltextures.begin(); it!=Totaltextures.end(); ++it) {
    //        if(Totaltextures[it]==IDofTexture) {
    //            Totaltextures.erase(it);
    //        }
    //    }
    return true;
}


// removes from Texture space by name, and from the map
bool
TextureManager::deleteTexture(char* FileNameOfTexture) {
    GLuint IDofTexture = Totaltextures[FileNameOfTexture];
    glDeleteTextures(1, &IDofTexture);
    Totaltextures.erase(FileNameOfTexture);
    return true;
}
