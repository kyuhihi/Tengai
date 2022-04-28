#pragma once

template <typename T>
void Safe_Delete(T& t)
{
	if (t)
	{
		delete t;
		t = nullptr;
	}
}
