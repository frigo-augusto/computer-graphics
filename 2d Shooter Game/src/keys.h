#ifndef KEYS_H
#define KEYS_H
#define KEY_BUFFER 10
#define INVALID_KEY -10000

void initKeys(int keys[])
{
   for (int i = 0; i < KEY_BUFFER; i++)
   {
      keys[i] = INVALID_KEY;
   }
}

void removeKey(int keys[], int key)
{
   for (int i = 0; i < KEY_BUFFER; i++)
   {
      if (keys[i] == key)
      {
         keys[i] = INVALID_KEY;
         break;
      }
   }
}

void addKey(int keys[], int key)
{
   removeKey(keys, key);
   for (int i = 0; i < KEY_BUFFER; i++)
   {
      if (keys[i] == INVALID_KEY)
      {
         keys[i] = key;
         break;
      }
   }
}

#endif // KEYS_H
