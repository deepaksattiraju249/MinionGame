// ObjToOpenGL.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//#include <GL/glut.h>
#include<iostream>
#include<fstream>
#include<string>
using namespace std;


// Model Structure
typedef struct Model
{
    int vertices;
    int positions;
    int texels;
    int normals;
	int objs;
    int faces;
	int mtls;
}
Model;

// 1
Model getOBJinfo(string fp)
{
    // 2
    Model model = {0};
 
    // 3
    // Open OBJ file
    std::ifstream inOBJ;
	inOBJ.open(fp);
    if(!inOBJ.good())
    {
        cout<< "ERROR OPENING OBJ FILE" << endl;
        exit(1);
    }
 
    // 4
    // Read OBJ file
    while(!inOBJ.eof())
    {
        // 5
        string line;
        getline(inOBJ, line);
        string type = line.substr(0,2);
 
        // 6
        if(type.compare("v ") == 0)
            model.positions++;
        else if(type.compare("vt") == 0)
            model.texels++;
        else if(type.compare("vn") == 0)
            model.normals++;
        else if(type.compare("f ") == 0)
            model.faces++;
		else if(type.compare("o ") == 0)
			model.objs++;
		else if(type.compare("us") == 0)
			model.mtls++;
    }
 
    // 7
    model.vertices = model.faces*3;
 
    // 8
    // Close OBJ file
    inOBJ.close();
 
    // 9
    return model;
}
void extractOBJdata(string fp, float **positions, int **faces, char** mtls, int *mtl_faces)
{
    // Counters
    int p = 0;
    int m = 0;
    int n = 0;
    int f = 0;
 
    // Open OBJ file
    std::ifstream inOBJ;
	
    inOBJ.open(fp);
    if(!inOBJ.good())
    {
        cout << "ERROR OPENING OBJ FILE" << endl;
		cout<<"blah";
        //exit(1);
    }
 
    // Read OBJ file
    while(!inOBJ.eof())
    {
        string line;
        getline(inOBJ, line);
        string type = line.substr(0,2);
		//string tok;
		//int j = 2;
        // Positions
        if(type.compare("v ") == 0)
		{// 1
    // Copy line for parsing
    char* l = new char[line.size()+1];
    memcpy(l, line.c_str(), line.size()+1);
 
    // 2
    // Extract tokens
    strtok(l, " ");
    for(int i=0; i<3; i++)
	{
        positions[p][i] = atof(strtok(NULL, " "));
		cout<<positions[p][i]<<"\t";
	}
	cout<<endl;
    // 3
    // Wrap up
    delete[] l;
    p++;
		}
 
        // Texels
 

// Faces
else if(type.compare("f ") == 0)
{
    char* l = new char[line.size()+1];
    memcpy(l, line.c_str(), line.size()+1);
 
    strtok(l, " ");
    for(int i=0; i<9; i++)
	{
		if(i == 1 || i == 4 || i == 7)
		{
			faces[f][i] = 0;
			cout<<i<<"n"<<faces[f][i]<<" ";
		}
		else
		{
			faces[f][i] = atof(strtok(NULL, "/ "));
			cout<<i<<"k"<<faces[f][i]<<" ";
		}
        
	}
	cout<<endl;
    delete[] l;
    f++;
}

	if(type.compare("us") == 0)
	{
		char* l = new char[line.size()+1];
        memcpy(l, line.c_str(), line.size()+1);
		cout<<line<<endl;
		strcpy(mtls[m],line.substr(line.find(" ")+1).c_str());
		cout<<line.substr(line.find(" ")+1).c_str()<<endl;
		int t = 0;
		while(mtls[m][t]!=NULL)
		{
			cout<<mtls[m][t];
			t++;
		}
		//getchar();
		mtl_faces[m] = f;
		m++;
		//delete[] ;
	}
    }
 
    // Close OBJ file
    inOBJ.close();
}

void writeMTL(string fp, char**mtl_names,float**mtl_kd, int m_count)
{
	ofstream outC;
    outC.open(fp);
    if(!outC.good())
    {
        cout << "ERROR CREATING C FILE" << endl;
        exit(1);
    }
	cout<<"Successfuly Created .c";
	for(int i = 0 ; i < m_count ; i++)
	{
		outC<<"const float "<<mtl_names[i]<< "[3] = {"<<mtl_kd[i][0]<<","<<mtl_kd[i][1]<<","<<mtl_kd[i][2]<<"};"<<endl;
		
	}
	outC.close();
	cout<<"YAY"<<endl;
}
void writeCvertices(string fp, string name, Model model)
{
    // Create C file
    ofstream outC;
    outC.open(fp);
    if(!outC.good())
    {
        cout << "ERROR CREATING C FILE" << endl;
        exit(1);
    }
	cout<<"Successfuly Created .c";
    // Write to C file
    outC << "// This is a .c file for the model: " << name << endl;
    outC << endl;
 
    // Header
    //outC << "#include " << "\"" << name << ".h" << "\"" << endl;
    outC << endl;
 
    // Vertices
    outC << "const int " << name << "Vertices = " << model.vertices << ";" << endl;
    outC << endl;
 
    // Close C file
    outC.close();
}

void writeCpositions(string fp, string name, Model model, int **faces, float **positions, int* mtls_face,char ** mtls)
{    
    // 2
    // Append C file
    ofstream outC;
    outC.open(fp, ios::app);
 
    // Positions
	for(int j = 0 ; j < model.mtls ; j++)
	{
	outC<<"// Material :"<<mtls[j]<<endl;
	
    outC << "const GLfloat mtl" << j << "[] = " << endl;
    outC << "{" << endl;
	for(int i=mtls_face[j]; i<mtls_face[j+1]||i<model.faces; i++)
    {
        // 3
        int vA = faces[i][0] - 1;
        int vB = faces[i][3] - 1;
        int vC = faces[i][6] - 1;
 
        // 4
        outC << positions[vA][0] << ", " << positions[vA][1] << ", " << positions[vA][2] << ", " << endl;
        outC << positions[vB][0] << ", " << positions[vB][1] << ", " << positions[vB][2] << ", " << endl;
        outC << positions[vC][0] << ", " << positions[vC][1] << ", " << positions[vC][2] << ", " << endl;
    }
    outC << "};" << endl;
    outC << endl;
	}


    // Close C file
    outC.close();
}

int GetInfoMTL(string fp)
{
	std::ifstream inOBJ;
    inOBJ.open(fp);
    if(!inOBJ.good())
    {
        cout << "ERROR OPENING OBJ FILE" << endl;
		cout<<"blah";
        //exit(1);
    }
	int m_count;
	while(!inOBJ.eof())
	{
		string line;
        getline(inOBJ, line);
        string type = line.substr(0,3);
		
		if(type.compare("# M") == 0)
		{
			m_count = atoi(line.substr(line.find(":")+1).c_str());
			break;
		}

	}
	inOBJ.close();
	return m_count;
}
void  Extract_MTL(string fp, char** mtl_name , float ** mtl_kd)
{
	// Open OBJ file
    std::ifstream inOBJ;
	int m = 0;
    inOBJ.open(fp);
    if(!inOBJ.good())
    {
        cout << "ERROR OPENING OBJ FILE" << endl;
		cout<<"blah";
        //exit(1);
    }
		while(!inOBJ.eof())
    {
        string line;
        getline(inOBJ, line);
        string type = line.substr(0,2);
		if(type.compare("ne") == 0)
		{
			strcpy(mtl_name[m], line.substr(line.find(" ")+1).c_str());
			cout<<mtl_name[m]<<endl;
		}
		else if(type.compare("Kd")==0)
		{
			char* l = new char[line.size()+1];
			memcpy(l, line.c_str(), line.size()+1);
 			strtok(l, " ");

			for(int i = 0 ; i < 3 ; i++)
			{			
				mtl_kd[m][i] = atof(strtok(NULL, " "));
				cout<<mtl_kd[m][i]<<" ";
			}
			cout<<endl;
			m++;
			delete[] l;
		}
	}
}
int main(int argc, char** argv)
 {
	
	string fp = "C:\\Users\\deepakSattiraju\\Desktop\\";
	string nameOBJ = "minion";
	string filepathOBJ = fp + nameOBJ + ".obj";
	string filepathH = fp + nameOBJ + ".h";
	string filepathC = fp + nameOBJ + ".c";
	
	Model model = getOBJinfo(filepathOBJ);
	cout << "Model Info" << endl;
	cout << "Positions: " << model.positions << endl;
	cout << "Texels: " << model.texels << endl;
	cout << "Normals: " << model.normals << endl;
	cout << "Faces: " << model.faces << endl;
	cout << "Vertices: " << model.vertices << endl;
	cout<<"Objects :"<<model.objs<<endl;
	cout<<"Materials:"<<model.mtls<<endl;
	getchar();

	//Model
	float **positions = (float**)malloc(sizeof(float*)*model.positions);    // XYZ
	for (int i = 0 ; i<model.positions ; i++)
	{
		positions[i] = (float*)malloc(sizeof(float)*3);
	}
	
	int **faces = (int**)malloc(sizeof(int*)*model.faces);    // XYZ
	for (int i = 0 ; i<model.faces ; i++)
	{
		faces[i] = (int*)malloc(sizeof(int)*9);
	}
	int *mtls_face = (int*)malloc(sizeof(int)*model.mtls);
	
	char **mtls = (char**)malloc(sizeof(char*)*model.mtls);
	for (int i = 0 ; i<model.mtls ; i++)
	{
		mtls[i] = (char*)malloc(sizeof(char)*10);
	}
	getchar();
	            // PTN PTN PTN
	
	extractOBJdata(filepathOBJ, positions, faces,mtls,mtls_face);
	cout<<"Done with Extraction..";
	cout<<mtls[0];
	//writeH(filepathH, nameOBJ, model);
	writeCvertices(filepathC, nameOBJ, model);
	cout<<"Vertices.. Written..";
	
	writeCpositions(filepathC, nameOBJ, model,faces, positions,mtls_face,mtls);
	cout<<"Position.. Written..";
	string filepathMTL = fp + nameOBJ + ".mtl";


	char** mtl_names ;
	float **mtl_kd ;
	int m_count = GetInfoMTL(filepathMTL);
	mtl_names = (char**)malloc(sizeof(char*)*m_count);
	for(int i = 0; i<m_count; i++)
	{
		mtl_names[i] = (char*)malloc(sizeof(char)*10);
	}
	mtl_kd = (float**)malloc(sizeof(float*)*m_count);
	for(int i = 0; i<m_count; i++)
	{
		mtl_kd[i] = (float*)malloc(sizeof(float)*3);
	}



	Extract_MTL(filepathMTL,mtl_names,mtl_kd);
	cout<<"FROM MAIN:" << mtl_names[0];
	filepathMTL = fp + nameOBJ + "_mtl.c";
	writeMTL(filepathMTL,mtl_names,mtl_kd, m_count);
	//writeCtexels(filepathC, nameOBJ, model, faces, texels);
	//writeCnormals(filepathC, nameOBJ, model, faces, normals);
	getchar();
	
	
	

  return 0;
}