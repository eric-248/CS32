
void removeEven(list<int>& li)
{
	list<int>::iterator i = li.begin();

	while(i != li.end()){
		if (*i % 2 == 0) {
			i = li.erase(i);
		}
		else {
			i++;
		}
		
	}

}

