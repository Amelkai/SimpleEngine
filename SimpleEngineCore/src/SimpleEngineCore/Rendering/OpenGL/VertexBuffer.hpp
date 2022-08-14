#pragma once 

#include <vector>

namespace SimpleEngine
{
	enum ShaderDataType
	{
		Float,
		Float2,
		Float3,
		Float4,
		Int,
		Int2,
		Int3,
		Int4
	};

	struct BufferElement
	{
		ShaderDataType type;
		uint32_t components_type;
		size_t components_count;
		size_t size;
		size_t offset;

		BufferElement(const ShaderDataType type);
	};

	class BufferLayout
	{
	public:
		BufferLayout(std::initializer_list<BufferElement> elements)
			: m_elements(std::move(elements))
		{
			size_t offset = 0;
			m_stride = 0;
			for (auto& elements : m_elements)
			{
				elements.offset = offset;
				offset += elements.size;
				m_stride += elements.size;
			}
		}

		const std::vector<BufferElement>& get_elements() const { return m_elements; };
		size_t get_stride() const { return m_stride; };

	private:
		std::vector<BufferElement> m_elements;
		size_t m_stride = 0;
	};

	class VertexBuffer
	{
	public:
		enum class EUsage
		{
			Static,
			Dynamic,
			Stream
		};

		VertexBuffer(const void* data, const size_t size, BufferLayout buffer_layout, const EUsage usage = VertexBuffer::EUsage::Static);
		~VertexBuffer();

		VertexBuffer(const VertexBuffer&) = delete;
		VertexBuffer& operator=(const VertexBuffer&) = delete;
		VertexBuffer& operator=(VertexBuffer&& vertexBuffer) noexcept;
		VertexBuffer(VertexBuffer&& vertexBuffer) noexcept;

		void bind() const;
		static void unbind();

		const BufferLayout& get_layout() const { return m_buffer_layout; };

	private:
		unsigned int m_id;
		BufferLayout m_buffer_layout;
	};
}