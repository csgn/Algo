#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct LLNODE
{
  uint index;
  string payload;
  LLNODE *next;
};

void showList(LLNODE *root)
{
  if (root == nullptr)
    return;

  LLNODE *walk = root;
  while (walk)
  {
    cout << walk->index << ": " << walk->payload << endl;
    walk = walk->next;
  }
}

string getLineFromFile(const string file, const uint length, const uint line)
{
  int i;
  string buffer;
  ifstream fs(file);

  i = 0;
  while (getline(fs, buffer) && i != line)
  {
    i++;
  }

  fs.close();

  return buffer;
}

uint getLengthFromFile(const string file)
{
  uint length;
  string buffer;
  ifstream fs(file);

  length = 0;
  while (getline(fs, buffer))
    length++;

  fs.close();
  return length;
}

LLNODE *getKeyFromFile(const string file, const uint length, const string key)
{
  int mid, left = 0, right = length - 1;
  int lmid, rmid;
  string buffer;
  string lbuffer, rbuffer;

  LLNODE *root = nullptr, *walk = nullptr;

  while (left <= right)
  {
    mid = (left + right) / 2;
    buffer = getLineFromFile(file, length, mid);

    if (not buffer.empty() and key == buffer)
    {
      root = new LLNODE();
      root->payload = buffer;
      root->index = mid + 1;
      walk = root;

      lmid = mid - 1;
      rmid = mid + 1;

      lbuffer = buffer;
      rbuffer = buffer;

      while (buffer == lbuffer)
      {
        lbuffer = getLineFromFile(file, length, lmid);

        if (buffer == lbuffer)
        {
          walk->next = new LLNODE();
          walk->next->payload = lbuffer;
          walk->next->index = lmid + 1;
          walk = walk->next;
          lmid--;
        }
        else
          break;
      }

      while (buffer == rbuffer)
      {
        rbuffer = getLineFromFile(file, length, rmid);

        if (buffer == rbuffer)
        {
          walk->next = new LLNODE();
          walk->next->payload = rbuffer;
          walk->next->index = rmid + 1;
          walk = walk->next;
          rmid++;
        }
        else
          break;
      }

      return root;
    }
    else if (key > buffer)
    {
      left = mid + 1;
    }
    else
    {
      right = mid - 1;
    }
  }

  return root;
}

int main(int argc, char const *argv[])
{
  uint length;
  uint index;
  const string file = argv[1];
  const string key = argv[2];
  LLNODE *root;
  length = getLengthFromFile(file);
  root = getKeyFromFile(file, length, key);

  showList(root);

  return 0;
}
