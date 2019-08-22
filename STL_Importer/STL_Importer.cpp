#include "STL_Importer.h"



STL_Importer::STL_Importer():
	m_name(""), m_faces()
{
}

void STL_Importer::Import(const std::string& i_file_path)
{
	std::ifstream in(i_file_path);
	if (in.is_open())
	{
		std::string input;
		in >> input;
		if (input != "solid")
			throw std::exception("Invalid file!\n");
		//STL file can include a name for the object
		std::getline(in, m_name);
		m_name = m_name.substr(1);

		//Starting reading faces
		while (true)
		{
			in >> input;

			if (input == "endsolid")
				break;
			if(in.eof())
				throw std::exception("Something wrong while file reading!\n");

			if (input != "facet")
				throw std::exception("Something wrong while file reading!\n");
			STL_Importer::Face t_face;
			
			//Can include normal for face
			std::getline(in, input);
			if (input.length() > 1)
			{
				t_face.m_hasNormal = true;
				input = input.substr(1);
				size_t pos = input.find(' ');
				std::string temp = input.substr(0, pos);
				if(temp != "normal")
					throw std::exception("Something wrong while file reading!\n");
				input = input.substr(pos + 1);
				for (size_t i = 0; i < 2; ++i)
				{
					pos = input.find(' ');
					temp = input.substr(0, pos);
					t_face.m_normal[i] = std::stof(temp);
					input = input.substr(pos + 1);
				}
				t_face.m_normal[2] = std::stof(input);
			}

			//Reading vertexes
			std::getline(in, input);
			if(input != "outer loop" && input != "\touter loop")
				throw std::exception("Something wrong while file reading!\n");

			for (size_t i = 0; i < 3; ++i)
			{
				in >> input;
				if(input != "vertex" && input != "\tvertex")
					throw std::exception("Something wrong while file reading!\n");
				std::array<float, 3> vertex;
				in >> vertex[0] >> vertex[1] >> vertex[2];
				t_face.m_vertexs[i] = vertex;
			}
			in >> input;
			if(input != "endloop" && input != "\tendloop")
				throw std::exception("Something wrong while file reading!\n");
			in >> input;
			if(input != "endfacet")
				throw std::exception("Something wrong while file reading!\n");
			m_faces.push_back(t_face);

		}

	}
	else
		throw std::exception("Wrong file path, check it again, please!\n");
}

const std::vector<STL_Importer::Face>& STL_Importer::GetFaces() const
{
	return m_faces;
}

std::vector<STL_Importer::Face>& STL_Importer::GetFaces()
{
	return m_faces;
}

STL_Importer::~STL_Importer()
{
}


/*
EXAMPLE OF STL FILE

solid cube_corner
		  facet normal 0.0 -1.0 0.0
			outer loop
			  vertex 0.0 0.0 0.0
			  vertex 1.0 0.0 0.0
			  vertex 0.0 0.0 1.0
			endloop
		  endfacet
		  facet normal 0.0 0.0 -1.0
			outer loop
			  vertex 0.0 0.0 0.0
			  vertex 0.0 1.0 0.0
			  vertex 1.0 0.0 0.0
			endloop
		  endfacet
		  facet normal -1.0 0.0 0.0
			outer loop
			  vertex 0.0 0.0 0.0
			  vertex 0.0 0.0 1.0
			  vertex 0.0 1.0 0.0
			endloop
		  endfacet
		  facet normal 0.577 0.577 0.577
			outer loop
			  vertex 1.0 0.0 0.0
			  vertex 0.0 1.0 0.0
			  vertex 0.0 0.0 1.0
			endloop
		  endfacet
		endsolid
*/