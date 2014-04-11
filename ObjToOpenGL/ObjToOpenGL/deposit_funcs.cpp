
void writeCtexels(string fp, string name, Model model, int **faces, float **texels)
{
    // Append C file
    ofstream outC;
    outC.open(fp, ios::app);
 
    // Texels
    outC << "const float " << name << "Texels[" << model.vertices*2 << "] = " << endl;
    outC << "{" << endl;
    for(int i=0; i<model.faces; i++)
    {
        int vtA = faces[i][1] - 1;
        int vtB = faces[i][4] - 1;
        int vtC = faces[i][7] - 1;
 
        outC << texels[vtA][0] << ", " << texels[vtA][1] << ", " << endl;
        outC << texels[vtB][0] << ", " << texels[vtB][1] << ", " << endl;
        outC << texels[vtC][0] << ", " << texels[vtC][1] << ", " << endl;
    }
    outC << "};" << endl;
    outC << endl;
 
    // Close C file
    outC.close();
}
 
void writeCnormals(string fp, string name, Model model, int **faces, float **normals)
{
    // Append C file
    ofstream outC;
    outC.open(fp, ios::app);
 
    // Normals
    outC << "const float " << name << "Normals[" << model.vertices*3 << "] = " << endl;
    outC << "{" << endl;
    for(int i=0; i<model.faces; i++)
    {
        int vnA = faces[i][2] - 1;
        int vnB = faces[i][5] - 1;
        int vnC = faces[i][8] - 1;
 
        outC << normals[vnA][0] << ", " << normals[vnA][1] << ", " << normals[vnA][2] << ", " << endl;
        outC << normals[vnB][0] << ", " << normals[vnB][1] << ", " << normals[vnB][2] << ", " << endl;
        outC << normals[vnC][0] << ", " << normals[vnC][1] << ", " << normals[vnC][2] << ", " << endl;
    }
    outC << "};" << endl;
    outC << endl;
 
    // Close C file
    outC.close();
}

void writeH(string fp, string name, Model model)
{
    // 2
    // Create H file
    ofstream outH;
    outH.open(fp);
    if(!outH.good())
    {
        cout << "ERROR CREATING H FILE" << endl;
        exit(1);
    }
 
    // 3
    // Write to H file
    outH << "// This is a .h file for the model: " << name << endl;
    outH << endl;
	outH << "// Positions: " << model.positions << endl;
	outH << "// Texels: " << model.texels << endl;
	outH << "// Normals: " << model.normals << endl;
	outH << "// Faces: " << model.faces << endl;
	outH << "// Vertices: " << model.vertices << endl;
	outH << endl;
 
	// Write declarations
	outH << "const int " << name << "Vertices;" << endl;
	outH << "const float " << name << "Positions[" << model.vertices*3 << "];" << endl;
	outH << "const float " << name << "Texels[" << model.vertices*2 << "];" << endl;
	outH << "const float " << name << "Normals[" << model.vertices*3 << "];" << endl;
	outH << endl;
    // 4
    // Close H file
    outH.close();
}
void print_OBJ_Info(Model model, float **positions, float **normals, float **texels,int **faces)
{
		cout << "Model Data" << endl;
	cout<<"Model Positions:"<<endl;
	for(int i = 0 ; i < model.positions;i++)
	{
		for(int j = 0; j<3 ; j++)
		{
			cout<<"\t"<<positions[i][j];
		}
		cout<<endl;
	}
	cout<<"Model Texels:"<<endl;
	for(int i = 0 ; i < model.texels;i++)
	{
		for(int j = 0; j<2 ; j++)
		{
			cout<<"\t"<<texels[i][j];
		}
		cout<<endl;
	}
	cout<<"Model Normals:"<<endl;
	for(int i = 0 ; i < model.normals;i++)
	{
		for(int j = 0; j<3 ; j++)
		{
			cout<<"\t"<<normals[i][j];
		}
		cout<<endl;
	}

}
