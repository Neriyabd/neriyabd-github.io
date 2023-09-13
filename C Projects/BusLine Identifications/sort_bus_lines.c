#include "sort_bus_lines.h"

void swap (BusLine *swap_loc, BusLine *orig_loc)
{
  BusLine temp = *swap_loc;
  *swap_loc = *orig_loc;
  *orig_loc = temp;
}

void bubble_sort (BusLine *start, BusLine *end)
{
  for (int i = 0; (start + i) < (end - 1); i++)
    {
      for (int j = 0; (start + j) < (end - i - 1); j++)
        {
          if ((start + j)->distance > (start + j + 1)->distance)
            {
              swap (start + j, start + j + 1);
            }
        }
    }
}

void quick_sort (BusLine *start, BusLine *end)
{
  if (start < (end - 1))
    {
      BusLine *result = (partition (start, end));
      quick_sort (start, (result));
      quick_sort (result + 1, end);
    }

}

BusLine *partition (BusLine *start, BusLine *end)
{
  int pivot = (end - 1)->duration;
  int i = -1;
  for (int j = 0; (start + j) < (end - 1); j++)
    {
      if ((start + j)->duration <= pivot)
        {
          i++;
          swap (start + i, start + j);
        }
    }
  swap (start + i + 1, (end - 1));
  return (start + i + 1);
}

