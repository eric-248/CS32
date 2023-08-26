
void removeBad(list<Restaurant*>& li)
{
	list<Restaurant*>::iterator i = li.begin();

	while(i != li.end()) {
		Restaurant* rp = *i;
		if (rp->stars() < 3) {
			i = li.erase(i);
			delete rp;
		}
		else {
			i++;
		}
	}
}

