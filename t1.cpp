#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// 定义链表节点
struct ListNode 
{
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) 
    {}
};

// 将数组转换为链表
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

// 归并两个有序链表
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

// 归并排序链表
static ListNode* mergeSort(ListNode* head)
{
    if (!head || !head->next) return head;

    // 使用快慢指针找到链表中间点
    ListNode* slow = head;
    ListNode* fast = head->next;
    while (fast && fast->next) 
    
   {
        slow = slow->next;
        fast = fast->next->next;
    }

    // 将链表拆分成两部分
    ListNode* mid = slow->next;
    slow->next = NULL;

    // 递归排序
    ListNode* left = mergeSort(head);
    ListNode* right = mergeSort(mid);

    // 合并排序的链表
    return mergeTwoLists(left, right);
}

// 将链表转换为字符串
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
        cerr << "无法打开输入文件" << endl;
        return 1;
    }
    if (!outFile.is_open()) {
        cerr << "无法打开输出文件" << endl;
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

    // 关闭文件
    inFile.close();
    outFile.close();

    return 0;
}
