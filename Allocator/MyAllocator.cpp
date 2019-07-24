#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <random>

using namespace std;


class MyAllocator
{
public:
	static const size_t mc_number = 8;

	struct Header
	{
	public:

		Header(const size_t size) :
			m_size(size), mp_next(nullptr), busy(false)
		{};

		~Header() = default;

		void ChangeBit(const size_t number)
		{
			size_t byte = number / 8;
			size_t bit = number % 8;
			m_bits[byte] ^= (1 << bit);
			CheckBusy();
		}

		void CheckBusy()
		{
			for (int i = 0; i < mc_number / 8; ++i)
				if ((int)m_bits[i] != 255)
				{
					busy = false;
					return;
				}
			busy = true;
		}

		size_t CountFree() const
		{
			if (busy)
				return 0;

			size_t ans = 0;
			for (int i = 0; i <mc_number / 8; ++i)
				if ((int)m_bits[i] != 255)
					for (int j = 0; j < 8; ++j)
						if ((m_bits[i] & (1 << j)) >> j == 0)
							++ans;
			return ans;
		}

		/* 1 - busy, 0 - free */
		bool GetBitInformation(const size_t number) const
		{
			size_t byte = number / 8;
			size_t bit = number % 8;
			return (m_bits[byte] & (1 << bit)) >> bit;
		}

		int FindFree() const
		{
			for (size_t i = 0; i < mc_number / 8; ++i)
			{
				if ((int)m_bits[i] != 255)
					for (size_t j = 0; j < 8; ++j)
						if ((m_bits[i] & (1 << j)) == 0)
							return i * 8 + j;
			}
			return -1;
		}

		const size_t m_size;
		Header *mp_next;
		unsigned char m_bits[mc_number / 8]{};
		bool busy;
	};

	MyAllocator(const size_t size) :
		mp_head(nullptr), mp_start_buffer(new char[size]), mp_end_buffer((char*)mp_start_buffer + size)
	{}

	~MyAllocator()
	{
		delete mp_start_buffer;
	}

	void* Allocate(const size_t size)
	{
		size_t c_size = 1;
		for (int i = 0; ; ++i)
		{
			if (c_size >= size)
				break;
			c_size *= 2;
		}

			if (mp_head == nullptr)
			{
				if ((char*)mp_end_buffer - (char*)mp_start_buffer >= sizeof(Header) + c_size * mc_number)
				{
					mp_head = new(mp_start_buffer) Header(c_size);
					mp_head->ChangeBit(0);
					return (char*)mp_head + sizeof(Header);
				}
				throw 1;
			}

			Header *p_cur = mp_head;
			bool found = false;
			while (true)
			{
				if (p_cur->m_size != c_size && p_cur->mp_next != nullptr)
				{
					p_cur = p_cur->mp_next;
					continue;
				}

				if (p_cur->m_size == c_size && p_cur->busy == false)
				{
					found = true;
					break;
				}

				break;
			}

			if (!found)
			{
				p_cur = mp_head;
				while (p_cur->mp_next != nullptr)
					p_cur = p_cur->mp_next;

				if ((char*)mp_end_buffer - (char*)p_cur - sizeof(Header) - p_cur->m_size*mc_number >= sizeof(Header) + c_size * mc_number)
				{
					Header* nH = new((char*)p_cur + sizeof(Header) + p_cur->m_size*mc_number) Header(c_size);
					nH->ChangeBit(0);
					p_cur->mp_next = nH;
					return (char*)nH + sizeof(Header);
				}
				throw 1;
			}

			int pos = p_cur->FindFree();
			p_cur->ChangeBit(pos);
			return (char*)p_cur + sizeof(Header) + pos * p_cur->m_size;
	}

	void Deallocate(const void* pointer)
	{
		Header *p_cur = mp_head;
		while (true)
		{
			if (p_cur->mp_next != nullptr && (char*)pointer - (char*)p_cur >= (char*)p_cur->mp_next - (char*)p_cur)
			{
				p_cur = p_cur->mp_next;
				continue;
			}

			break;
		}

		size_t pos = ((char*)pointer - (char*)p_cur - sizeof(Header)) / p_cur->m_size;
		p_cur->ChangeBit(pos);
		p_cur->busy = false;
	}

	friend ostream& operator << (ostream& out, const MyAllocator& al)
	{
		MyAllocator::Header *p_cur = al.mp_head;
		while (true)
		{
			cout << "Memory: " << p_cur << ", size: " << p_cur->m_size << ", free cells: " << p_cur->CountFree() << endl;
			if (p_cur->mp_next == nullptr)
				break;
			p_cur = p_cur->mp_next;
		}

		return out;
	}

private:
	Header* mp_head;
	void* mp_start_buffer;
	void* mp_end_buffer;
};

void TestAllocator(MyAllocator& al, const size_t num_of_iterat)
{
	vector<void*> pointers;
	for (size_t i = 0; i < num_of_iterat; ++i)
	{
		int posbility = rand() % 100;
		if (posbility > 80 && pointers.size() != 0)
		{
			cout << "Dealocating...\n";
			size_t pos = rand() % pointers.size();
			al.Deallocate(pointers[pos]);
		}
		else
		{
			size_t size = rand() % 512;
			cout << "Allocating...\n";
			try
			{
				pointers.push_back(al.Allocate(size));
				cout << "Allocated " << pointers.back() << endl;
			}
			catch (int)
			{
				cout << "Something gone wrong while allocating...\n";
				continue;
			}
		}
	}
}
