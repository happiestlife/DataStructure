#include<stdio.h>
#define MAX 20;
typedef struct Order {
	struct MList* head;
	int candle_num;
	int spoon_num;
}Order;
typedef struct MList {
	char menu_name[MAX];
	char icecream[MAX];
	char HP_icecream[6][MAX];
	int num;
	struct MList* link;
}MList;

void Ordering() {
	Order* order = (Order*)malloc(sizeof(Order));
	if(!order)
		MemoryError();
	init_Order(order);
	int type = 0;
	while (1) {
		type = Show_MenuType();
		MenuList(order, type);
		printf("1. �����ϱ�\n2. �� �ֹ��ϱ�\n");
		scanf_s("%d", &type);
		if (type == 1) {
			//���� handpack�̳� ���̽�ũ������ũ�� �ֹ����� ���, ������ �ð��̳� ���ϴ� ������ ����, ���̽�ũ�� ����ũ�ΰ�� �кҰ��� �Է¹ޱ�
			//����ϱ�
			break;
		}
	}
}
void MemoryError() {
	printf("memory assignment error");
	exit(1);
}
void init_Order(Order* order) {
	order->candle_num = 0;
	order->spoon_num = 0;
	order->head = NULL;
}

int Show_MenuType() {
	printf("���ϴ� �׸��� �����ϼ���.\n");
	for (int type = 0; ;) {
		printf("***********************\n");
		printf("    1. IceCream\n");
		printf("    2. IceCreamCake\n");
		printf("    3. Beverage\n");
		printf("    4. Coffee\n");
		printf("***********************\n");
		scanf_s("%d", &type);
		if (type < 1 || type>4) {
			printf("1~4�� �׸���̿��� ����ּ���.\n");
			continue;
		}
		return type;
	}
}

void MenuList(Order* order, int type) {
	int IC_type = 0;
	switch (type) {
	case 1:
		IC_type = IcecreamList();
		IC_select(order, IC_type);
		break;
	case 2:
		IcecreamCakeList();
		else_select(order);
		break;
	case 3:
		BeverageList();
		else_select(order);
		break;
	case 4:
		CoffeeList();
		else_select(order);
		break;
	}
	return;
}
void store(Order* order,Mlist* node){
	if (order->head == NULL) {
		node->link = NULL;
		order->head = node;
	}
	else {
		node->link = order->head;
		order->head = node;
	}
}
int IcecreamList() {
	int type = 0, Con_type = 0, HP_type = 0, _num = 0;
	MList* node = (MList*)malloc(sizeof(MList));
	if (!node)
		MemoryError();

	printf("���ϴ� �׸��� �����ϼ���.\n");
	for (; ;) {													// Con&Cup�� HandPack�� �ϳ� ����
		printf("***********************\n");
		printf("    1. Con & Cup\n");
		printf("    2. HandPack\n");
		printf("***********************\n");
		scanf_s("%d", &type);
		if (type < 1 || type>2) {
			printf("1~4�� �׸���̿��� ����ּ���.\n");
			continue;
		}
		break;
	}

	printf("���ϴ� ����� �����ϼ���.\n");
	if (type == 1) {
		for (; ;) {
			printf("-----------------------\n");
			printf("    1. �̱۷��ַ�\n");
			printf("    2. �̱�ŷ\n");
			printf("    3. �����ִϾ�\n");
			printf("    4. �����ַ�\n");
			printf("-----------------------\n");
			scanf_s("%d", &Con_type);
			if (type < 1 || type>4) {
				printf("1~4�� �׸���̿��� ����ּ���.\n");
				continue;
			}
			break;
		}
		printf("��� �����Ͻ� �ǰ���?\n");
		while () {
			scanf_s("%d", _num);								// �ֹ��� �Ѱ��̻�
			if (_num <= 0) {
				printf("�Ѱ��̻� �ֹ����ּ���.\n");
				continue;
			}
			break;
		}
		switch (Con_type) {
		case 1:
			strcpy(node->menu_name, "�̱۷��ַ�");
			node->num = _num;
			break;
		case 2:
			strcpy(node->menu_name, "�̱�ŷ");
			node->num = _num;
			break;
		case 3:
			strcpy(node->menu_name, "�����ִϾ�");
			node->num = _num;
			break;
		case 4:
			strcpy(node->menu_name, "�����ַ�");
			node->num = _num;
			break;
		}
		return 1;
	}
	else {
		printf("-----------------------\n");
		printf("    1. ����Ʈ\n");
		printf("    2. ����\n");
		printf("    3. �йи�\n");
		printf("    4. ��������\n");
		printf("-----------------------\n");
		return 2;
	}
	//���̽�ũ�� ����Ʈ ����
}

void IcecreamCakeList() {
	printf("���ϴ� �޴��� �����ϼ���.\n");
	//���̽�ũ�� ����ũ ����Ʈ ����
}

void BeverageList() {
	printf("���ϴ� �޴��� �����ϼ���.\n");
	//����� ����Ʈ ����
}

void CoffeeList() {
	printf("���ϴ� �޴��� �����ϼ���.\n");
	//Ŀ�� ����Ʈ ����
}
Order* IC_select(Order* order, int type) {
	if (type == 1) {

	}
	else {

	}
}
Order* else_select(Order* order) {
	int _num = 0;
	char name[MAX];
	int menu = 0, type = 0, spoon_num = 0, candle_num = 0;

	//���� �޴��� handpack�� ��� ������ ���� �ʰ� ���̽�ũ���� �ֹ��ޱ� 
	scanf_s("%d", &menu);
	MList* node = (MList*)malloc(sizeof(MList));		// �ֹ����� ���Ḯ��Ʈ(����)�� �����ϱ�
	if (!node)
		MemoryError();
	//���ϴ� �׸��� Ž���ϼ� ã�� �޴��̸��� ������ ����
	printf("���ϴ� ������ �Է��Ͻʽÿ�.\n");
	scanf_s("%d", &_num);

	strcpy(node->menu_name, name);
	node->num = _num;
	if (order->head == NULL) {
		node->link = NULL;
		order->head = node;
	}
	else {
		node->link = order->head;
		order->head = node;
	}

	printf("1. �����ϱ�\n2. �� �ֹ��ϱ�\n");
	scanf_s("%d", &type);
	if (type == 1) {
		//���� handpack�̳� ���̽�ũ������ũ�� �ֹ����� ���, ������ �ð��̳� ���ϴ� ������ ����, ���̽�ũ�� ����ũ�ΰ�� �кҰ��� �Է¹ޱ�
		//����ϱ�
	}
	else 
		return;
}

int main() {
	Show_MenuType();
}
