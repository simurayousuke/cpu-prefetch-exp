#include <iostream>
#include <chrono>
#include <vector>
#include <list>
using namespace std;

#define SUB_COUNT 100
#define DEPTH 10

template<template <typename, typename> class ContainerType>
class GameObject
{
private:
	float position[3] = { 0,0,0 };
	float rotation[3] = { 0,0,0 };
	float scale[3] = { 1,1,1 };

	float matrix[4][4] = {
		{1,0,0,0},
		{0,1,0,0},
		{0,0,1,0},
		{0,0,0,1}
	};

	ContainerType<GameObject*, std::allocator<GameObject*>> children;

	void UpdateMatrixForChildren()
	{
		for (auto child : children)
			child->UpdateMatrix();
	}

public:
	void AddChild(GameObject<ContainerType>* gameOjbect)
	{
		children.push_back(gameOjbect);
	}


	GameObject() {
		for (auto i = 0; i < 3; ++i) {
			position[i] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			rotation[i] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			scale[i] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		}
	}

	GameObject(float* pos, float* rot, float* scl) {
		memcpy_s(position, 3 * sizeof(float), pos, 3 * sizeof(float));
		memcpy_s(rotation, 3 * sizeof(float), rot, 3 * sizeof(float));
		memcpy_s(scale, 3 * sizeof(float), scl, 3 * sizeof(float));
	}

	void UpdateMatrix() {
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				matrix[i][j] = (i == j) ? 1.0f : 0.0f;
			}
		}

		// Rotation matrices
		float cx = cos(rotation[0]);
		float sx = sin(rotation[0]);
		float cy = cos(rotation[1]);
		float sy = sin(rotation[1]);
		float cz = cos(rotation[2]);
		float sz = sin(rotation[2]);

		// Rotate X
		matrix[1][1] = cx;
		matrix[1][2] = -sx;
		matrix[2][1] = sx;
		matrix[2][2] = cx;

		// Rotate Y
		matrix[0][0] = cy;
		matrix[0][2] = sy;
		matrix[2][0] = -sy;
		matrix[2][2] *= cy;

		// Rotate Z
		matrix[0][0] *= cz;
		matrix[0][1] *= -sz;
		matrix[1][0] *= sz;
		matrix[1][1] *= cz;

		// Scale
		matrix[0][0] *= scale[0];
		matrix[1][1] *= scale[1];
		matrix[2][2] *= scale[2];

		// Translation
		matrix[3][0] = position[0];
		matrix[3][1] = position[1];
		matrix[3][2] = position[2];

		UpdateMatrixForChildren();
	}
};

template<class T>
void InitData(size_t depth, size_t maxDepth, size_t size, T& node)
{
	if (depth >= maxDepth)
		return;
	for (auto i = 0; i < size; ++i)
	{
		T* t = new T();
		node.AddChild(t);
		InitData(++depth, maxDepth, size, *t);
	}
}


int main()
{
	GameObject<vector> arrayRoot;
	GameObject<list> llistRoot;

	InitData(0, DEPTH, SUB_COUNT, arrayRoot);
	InitData(0, DEPTH, SUB_COUNT, llistRoot);

	for (auto i = 0; i < 10; ++i)
	{
		cout << "---------------------------------------" << endl;
		{
			auto start = chrono::steady_clock::now();

			llistRoot.UpdateMatrix();

			auto end = chrono::steady_clock::now();
			auto diff = end - start;
			auto time = chrono::duration <double, milli>(diff).count();
			printf("llist: %2.3f ms ( %2.1f FPS)\r\n", time, 1000.0 / time);
		}

		{
			auto start = chrono::steady_clock::now();

			arrayRoot.UpdateMatrix();

			auto end = chrono::steady_clock::now();
			auto diff = end - start;
			auto time = chrono::duration <double, milli>(diff).count();
			printf("array: %2.3f ms ( %2.1f FPS)\r\n", time, 1000.0 / time);
		}
	}
	cout << "---------------------------------------" << endl;
	system("pause");
	return 0;
}