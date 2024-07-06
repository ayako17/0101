#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// ��������ڵ�
struct ListNode 
{
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) 
    {}
};

// ������ת��Ϊ����
static ListNode* arrayToList(const vector<int>& nums)
{
    if (nums.empty()) return NULL;
    ListNode* head = new ListNode(nums[0]);
    ListNode* current = head;
    for (size_t i = 1; i < nums.size(); ++i) {
        current->next = new ListNode(nums[i]);
        current = current->next;
    }
    return head;
}

// �鲢������������
static ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) 
{
    if (!l1) return l2;
    if (!l2) return l1;

    if (l1->val < l2->val) {
        l1->next = mergeTwoLists(l1->next, l2);
        return l1;
    }
    else {
        l2->next = mergeTwoLists(l1, l2->next);
        return l2;
    }
}

// �鲢��������
static ListNode* mergeSort(ListNode* head)
{
    if (!head || !head->next) return head;

    // ʹ�ÿ���ָ���ҵ������м��
    ListNode* slow = head;
    ListNode* fast = head->next;
    while (fast && fast->next) 
    
   {
        slow = slow->next;
        fast = fast->next->next;
    }

    // �������ֳ�������
    ListNode* mid = slow->next;
    slow->next = NULL;

    // �ݹ�����
    ListNode* left = mergeSort(head);
    ListNode* right = mergeSort(mid);

    // �ϲ����������
    return mergeTwoLists(left, right);
}

// ������ת��Ϊ�ַ���
static string listToString(ListNode* head) 
{
    if (!head) return "";
    ostringstream oss;
    ListNode* current = head;
    while (current) 
    {
        oss << current->val;
        if (current->next) oss << " ";
        current = current->next;
    }
    return oss.str();
}

int main01() 
{
    ifstream inFile("in.txt");
    ofstream outFile("out.txt");

    if (!inFile.is_open()) 
    {
        cerr << "�޷��������ļ�" << endl;
        return 1;
    }
    if (!outFile.is_open()) {
        cerr << "�޷�������ļ�" << endl;
        return 1;
    }

    string line;
    getline(inFile, line);
    istringstream iss(line);
    vector<int> nums;
    int num;
    while (iss >> num) 
    {
        nums.push_back(num);
    }

    ListNode* head = arrayToList(nums);
    head = mergeSort(head);
    string result = listToString(head);

    outFile << result << endl;

    // �ر��ļ�
    inFile.close();
    outFile.close();

    return 0;
}
