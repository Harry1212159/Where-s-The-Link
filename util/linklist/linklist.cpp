struct NODE {
    int data;
    NODE* next;
};

struct ROW {
    NODE* rowHead;
    ROW* next;
};


NODE* CreateNode(int data) {
    NODE* node = new NODE;
    node->data = data;
    node->next = NULL;
    return node;
}

ROW* CreateRow() {
    ROW* row = new ROW;
    row->rowHead = NULL;
    row->next = NULL;
    return row;
}

void AddRow(ROW* &map) {
    if (map == NULL) {
        map = CreateRow();
    } else {
        ROW* arow = CreateRow();
        arow->next = map;
        map = arow;
    }
}

void AddCell(ROW* &row, int data) {
    if (row->rowHead == NULL) {
        row->rowHead = CreateNode(data);
    } else {
        NODE* anode = CreateNode(data);
        anode->next = row->rowHead;
        row->rowHead = anode;
    }
}

int AccessMap(ROW* map, int x, int y) {
    int rowIndex = 0;
    ROW* row = map;
    while (row != NULL && rowIndex != y) {
        row = row->next;
        rowIndex++;
    }

    int colIndex = 0;
    NODE* col = row->rowHead;
    while (col != NULL && colIndex != x) {
        col = col->next;
        colIndex++;
    }
    return col->data;
}

void ChangeMap(ROW* map, int x, int y, int data) {
    int rowIndex = 0;
    ROW* row = map;
    while (row != NULL && rowIndex != y) {
        row = row->next;
        rowIndex++;
    }

    int colIndex = 0;
    NODE* col = row->rowHead;
    while (col != NULL && colIndex != x) {
        col = col->next;
        colIndex++;
    }
    if (rowIndex == y && colIndex == x) {
        col->data = data;
    }
}

void PrintMap(ROW* map) {
    ROW* row = map;
    while (row != NULL) {
        NODE* col = row->rowHead;
        while (col != NULL) {
            cout << col->data;
            col = col->next;
        }
        cout << endl;
        row = row->next;
    }
}

void DeleteMap(ROW* &map) {
    ROW* row = map;
    while (row != NULL) {
        NODE* col = row->rowHead;
        while (col != NULL) {
            NODE* dnode = col;
            col = col->next;
            delete dnode;
        }
        ROW* drow = row;
        row = row->next;
        delete drow;
    }
    map = NULL;
}