#pragma once

#include <GL/glew.h>

#include "collections/array-list/ArrayList.h"

namespace opengl
{

	struct VertexBufferElement
	{
		unsigned int type;
		unsigned int count;
		unsigned char normalized;

		static unsigned int GetSizeOfType(unsigned int type)
		{
			switch (type)
			{
			case GL_FLOAT: return 4;
			case GL_UNSIGNED_INT: return 4;
			case GL_UNSIGNED_BYTE: return 1;
			}

			//	ASSERT(false);
			return 0;
		}

	};

	class VertexBufferLayout
	{
	private:
		collection::ArrayList<VertexBufferElement*> m_Elements;
		unsigned int m_Stride;
	public:
		VertexBufferLayout()
			: m_Stride(0) {}

		template<typename T>
		void Push(unsigned int count)
		{
			static_assert(false);
		}

		template<>
		void Push<float>(unsigned int count)
		{

			VertexBufferElement* vbe = new VertexBufferElement{ GL_FLOAT, count, GL_FALSE };
			m_Elements.Add(vbe);
			m_Stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;

		}

		template<>
		void Push<unsigned int>(unsigned int count)
		{
			VertexBufferElement* vbe = new VertexBufferElement{ GL_UNSIGNED_INT, count, GL_FALSE };
			m_Elements.Add(vbe);
			m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
		}

		template<>
		void Push<unsigned char>(unsigned int count)
		{
			VertexBufferElement* vbe = new VertexBufferElement{ GL_UNSIGNED_BYTE, count, GL_TRUE };
			m_Elements.Add(vbe);
			m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;

		}

		inline const collection::ArrayList<VertexBufferElement*>& GetElements() const { return m_Elements; }
		inline unsigned int GetStride() const { return m_Stride; }

	};
}

