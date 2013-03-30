#pragma once
class Vertex
{
	float x;
	float y;
	float z;
	float w;

public:
	Vertex(float x, float y, float z, float w);
	
	float operator[](int index);

	Vertex(void);
	~Vertex(void);
};

