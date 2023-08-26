
void listAll(const MenuItem* m, string path) // two-parameter overload
{
    if (m == nullptr)
        return;

    if (path != "")
        path += "/";

    path += m->name();
    cout << path << endl;

    const vector<MenuItem*>* items = m->menuItems();
    if (items != nullptr) {
        for (int i = 0; i < items->size(); i++) {
            MenuItem* temp = (*items)[i];
            listAll(temp, path);
        }
    }
}
