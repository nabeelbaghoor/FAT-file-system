#include<iostream>
using namespace std;
#pragma warning(disable : 4996)
template<class T>
class Node {
public:
	Node<T>* next;
public:
	Node()
	{
		next = nullptr;
	}
	Node(T d, Node<T>* n = nullptr)
		:data(d), next(n)
	{
	}
	T& getData()
	{
		return data;
	}
	~Node()
	{
	}
	friend class FileSytem;
};
template<class T>
class LinkList {
	Node<T>* head;
	Node<T>* tail;
	int size;
public:
	class iteratr {
	public:
		Node<T>* curr;
	public:
		iteratr(Node<T>* ptr)
		{
			curr = ptr;
		}
		bool operator!=(iteratr obj)
		{
			return curr != obj.curr;
		}
		Node<T>* operator++()
		{
			curr = curr->next;
			return curr;
		}
		T operator*()
		{
			return curr->data;
		}
		Node<T>* getNodePtr()
		{
			return curr;
		}
		friend class FileSytem;
	};
	iteratr begin()
	{
		return iteratr(head);
	}
	iteratr end()
	{
		return iteratr(nullptr);
	}
	LinkList()
	{
		head = tail = nullptr;
		size = 0;
	}
	void InsertAtStart(T d)
	{
		Node<T>* temp = new Node<T>(d, head);
		if (head == nullptr)
			tail = temp;
		head = temp;
		size++;
	}
	void InsertAtEnd(T d)
	{
		Node<T>* temp = new Node<T>(d, nullptr);
		if (head == nullptr)
			head = tail = temp;
		else
		{
			tail->next = temp;
			tail = temp;
		}
		size++;
	}
	void InsertAtEnd()
	{
		Node<T>* temp = new Node<T>;
		temp->next = nullptr;
		if (head == nullptr)
			head = tail = temp;
		else
		{
			tail->next = temp;
			tail = temp;
		}
		size++;
	}
	void InsertAtEnd(Node<T>* Dptr)
	{
		Dptr->next = nullptr;
		if (head == nullptr)
			head = tail = Dptr;
		else
		{
			tail->next = Dptr;
			tail = Dptr;
		}
		size++;
	}
	void InsertInSortedOrder(T d)
	{

		if (head == nullptr || d < head->data)
			InsertAtStart(d);
		else
		{
			Node<T>* curr = head;
			while (curr->next != nullptr && curr->next->data > d)
				curr = curr->next;
			Node<T>* t = new Node<T>(d);
			t->next = curr->next;
			curr->next = t;
		}
		size++;
	}
	void RemoveFromStart()
	{
		if (head != nullptr)
		{
			if (head == tail)
			{
				delete head;
				head = tail = nullptr;
			}
			else
			{
				Node<T>* temp = head->next;
				delete head;
				head = temp;
			}
			size--;
		}
	}
	void RemoveFromEnd()
	{
		if (head != nullptr)
		{
			if (head == tail)
			{
				delete head;
				head = tail = nullptr;
			}
			else
			{
				Node<T>* curr = head;
				while (curr->next != tail)
					curr = curr->next;
				curr->next = nullptr;
				delete tail;
				tail = curr;

			}
			size--;
		}
	}
	void Remove(T d)
	{
		if (head != nullptr)
		{
			if (head->data == d)
				RemoveFromStart();
			else if (tail->data == d)
				RemoveFromEnd();
			else
			{
				Node<T>* prev, * curr;
				prev = curr = head;
				while (curr != nullptr && curr->data != d)
				{
					prev = curr;
					curr = curr->next;
				}
				if (curr != nullptr)
				{
					prev->next = curr->next;
					delete curr;
				}
			}
			size--;
		}
	}
	void RemoveWithoutDeallocate(T d)
	{
		if (head != nullptr)
		{
			if (head->data == d)
				head = head->next;
			else
			{
				Node<T>* prev = head;
				Node<T>* curr = head;
				while (curr != nullptr && curr->data != d)
				{
					prev = curr;
					curr = curr->next;
				}
				if (curr != nullptr)
					prev->next = curr->next;
			}
			size--;
		}
	}
	bool Search(T d)
	{
		Node<T>* curr = head;
		while (curr != nullptr)
		{
			if (curr->data == d)
				return true;
			curr = curr->next;
		}
		return false;
	}
	~LinkList()
	{
		while (size--)
			RemoveFromStart();
	}
	friend class FileSystem;
};
class Block {
	int start_sector_ID;
	int total_sectors;
public:
	Block()///not correct
	{
		start_sector_ID = 0;
		total_sectors = 0;
	}
	Block(int start_ID, int total)
		:start_sector_ID(start_ID), total_sectors(total)
	{}
	void print()
	{
		cout << start_sector_ID << endl << total_sectors << endl << endl;
	}
	Block(const Block& obj)//not const yet
	{
		start_sector_ID = obj.start_sector_ID;
		total_sectors = obj.total_sectors;
	}
	bool operator<(const Block& obj)
	{
		return (start_sector_ID < obj.start_sector_ID);
	}
	bool operator>(const Block& obj)
	{
		return (start_sector_ID > obj.start_sector_ID);
	}
	Block& operator=(Block obj)
	{
		start_sector_ID = obj.start_sector_ID;
		total_sectors = obj.total_sectors;
	}//mb not req
	bool operator==(Block obj)
	{
		return (start_sector_ID == obj.start_sector_ID && total_sectors == total_sectors);
	}
	bool operator!=(Block obj)
	{
		return !(start_sector_ID == obj.start_sector_ID && total_sectors == total_sectors);
	}
	~Block() {}
	friend class FileSystem;
};
class File {
	char* name;
	int size;
	LinkList<Block>blocks;
public:
	File()
	{
		name = nullptr;
		size = 0;
	}
	File(char* n, int s)
		:size(s)
	{
		name = new char[strlen(n) + 1];
		strcpy(name, n);
		name[strlen(n)] = 0;
	}
	char* GetName()
	{
		return name;
	}
	void UpdateSize(int input)
	{
		size = input;
	}
	int GetSize()
	{
		return size;
	}
	bool operator==(File obj)//compares only names
	{
		return (!strcmp(name, obj.name));
	}
	bool operator!=(File obj)//compares only names
	{
		return (strcmp(name, obj.name));
	}
	File& operator=(File obj)
	{
		size = obj.size;
		if (name != nullptr)
			delete[]name;
		name = new char[strlen(obj.name) + 1];
		strcpy(name, obj.name);
		name[strlen(obj.name)] = 0;
		return *this;
	}
	friend class FileSystem;
	~File()
	{
		if (name != nullptr)
			delete[]name;
	}
};
class FileSystem {
	LinkList<Block>pool;
	LinkList<File>Files;
	char* disk;
	int numOfSectors;
	int sizeOfSectors;
	int numOfSectorsInPool;
public:
	FileSystem(int num_of_sectors, int size_of_sectors)
		:numOfSectors(num_of_sectors), sizeOfSectors(size_of_sectors)
	{
		numOfSectorsInPool = numOfSectors;
		disk = new char[numOfSectors * sizeOfSectors + 1];
		disk[numOfSectors * sizeOfSectors] = 0;
		pool.InsertAtEnd(Block(0, numOfSectors));
	}
	void PrintBlock(Node<Block>* b)
	{
		int FirstByte = (b->getData().start_sector_ID) * sizeOfSectors;
		int LastByte = ((b->getData().start_sector_ID) * sizeOfSectors) + ((b->getData().total_sectors) * sizeOfSectors) - 1;
		for (int i = FirstByte; i <= LastByte; i++)
			cout << disk[i];
		//cout << endl;
	}
	bool SearchFileName(char* fname) /////mb     //mb
	{
		if (fname != nullptr)
		{
			for (LinkList<File>::iteratr itr = Files.begin(); itr != Files.end(); ++itr)
				if (!strcmp(itr.getNodePtr()->getData().name, fname))//mb//mb//must req to be checked..
					return true;
		}
		return false;

	}
	void DeleteFile(char* fname)
	{
		for (LinkList<File>::iteratr itr = Files.begin(); itr != Files.end(); ++itr)
		{
			if (!strcmp((*itr).name, fname))
			{
				for (LinkList<Block>::iteratr i = (*itr).blocks.begin(); i != (*itr).blocks.end(); ++i)
				{
					(*itr).blocks.RemoveWithoutDeallocate(*i);//extremly enefficient
					pool.InsertInSortedOrder(*i);
					numOfSectorsInPool += (*i).total_sectors;
				}
				Files.Remove(*itr);
				break;
			}
		}
		MergePool();
	}
	void MergePool()
	{
		if (pool.size > 1)
		{
			int FirstByte, LastByte;
			for (LinkList<Block>::iteratr i = pool.begin(); i != pool.end(); ++i)
			{
				LastByte = (((*i).start_sector_ID) * sizeOfSectors) + (((*i).total_sectors) * sizeOfSectors) - 1;
				for (LinkList<Block>::iteratr j = pool.begin(); j != pool.end(); ++j)
				{
					FirstByte = ((*j).start_sector_ID) * sizeOfSectors;

					if (LastByte == FirstByte - 1)
					{
						i.getNodePtr()->getData().total_sectors += (*j).total_sectors;
						pool.Remove(*j);
						break;
					}
				}
			}
		}
	}
	Block Shrink(int sizeToShrink)
	{
		pool.head->getData().start_sector_ID += sizeToShrink;
		pool.head->getData().total_sectors -= sizeToShrink;
		return Block(pool.head->getData().start_sector_ID - sizeToShrink, sizeToShrink);
	}
	bool SaveFile(char* fname, char* fcontent, int fsize)
	{
		if (((numOfSectorsInPool * sizeOfSectors) < fsize) || SearchFileName(fname))
			return false;
		else
		{
			int FirstByte, LastByte, index = 0;
			Files.InsertAtEnd(File(fname, fsize));
			int sectors = fsize / sizeOfSectors;
			for (LinkList<Block>::iteratr itr = pool.begin(); itr != pool.end() && sectors > 0; ++itr)
			{

				if ((*itr).total_sectors <= sectors)
				{
					pool.RemoveWithoutDeallocate(*itr);
					Files.tail->getData().blocks.InsertAtEnd(itr.getNodePtr());//
					sectors -= (*itr).total_sectors;//mb
					numOfSectorsInPool -= (*itr).total_sectors;////mb


					FirstByte = ((*itr).start_sector_ID) * sizeOfSectors;
					LastByte = (((*itr).start_sector_ID) * sizeOfSectors) + (((*itr).total_sectors) * sizeOfSectors) - 1;
					for (int i = FirstByte; i <= LastByte; i++)
						disk[i] = fcontent[index++];
				}
			}
			if (sectors > 0)
			{
				Block temp = Shrink(sectors);
				Files.tail->getData().blocks.InsertAtEnd(temp);//mb it will work
				numOfSectorsInPool -= sectors;///mb

				FirstByte = (temp.start_sector_ID) * sizeOfSectors;
				LastByte = ((temp.start_sector_ID) * sizeOfSectors) + ((temp.total_sectors) * sizeOfSectors) - 1;
				for (int i = FirstByte; i <= LastByte; i++)
					disk[i] = fcontent[index++];
			}
			//
			return true;
		}
	}
	void ReadFile(char* fname)
	{
		bool flag = 0;
		for (LinkList<File>::iteratr itr = Files.begin(); itr != Files.end(); ++itr)
		{
			if (!strcmp((*itr).name, fname))//mb//mb//must req to be checked..
			{
				for (LinkList<Block>::iteratr i = (*itr).blocks.begin(); i != (*itr).blocks.end(); ++i)
				{
					PrintBlock(i.getNodePtr());
					cout << endl;///mb req
				}
				flag = 1;
				break;
			}
		}
		if (!flag)
			cout << "\nFile Not Found!!\n";
	}
	~FileSystem()
	{
		if (disk != nullptr)
			delete[]disk;
	}
};
void menu()
{
	int sizeOfSector, noOfSectors, size, num;
	char name[100];
	char content[100];
	cout << "Pls Enter the Size of Sector:\t";
	cin >> sizeOfSector;
	cout << "Pls Enter the No. of Sectors:\t";
	cin >> noOfSectors;
	FileSystem file(noOfSectors, sizeOfSector);
	cout << "Follow this menu:\n";
	cout << "Press 0 for SaveFile\n";
	cout << "Press 1 for DeleteFile\n";
	cout << "Press 2 for RedFile\n";
	while (1)
	{
		cin >> num;
		switch (num)
		{
		case 0:
			cout << "Enter the name of the file:\n";
			cin >> name;
			cout << "Enter the size of the file in  bytes:\n";
			cin >> size;
			cout << "Enter the content\n";
			cin >> content;
			file.SaveFile((char*)name, (char*)content, size);
		case 1:
			cout << "Enter the name of the file:\n";
			cin >> name;
			file.DeleteFile((char*)name);
		case 2:
			cout << "Enter the name\n";
			cin >> name;
			file.ReadFile((char*)name);
		}
	}
}
int main()
{
	//menu();
	system("pause");
}

