#include "test_bus_lines.h"
#include "sort_bus_lines.h"
#define TRUE 1
#define FALSE 0

int is_sorted_by_distance (BusLine *start, BusLine *end)
{
  bubble_sort (start, end);
  for (int i = 0; start + i < (end - 1); i++)
    {
      if ((start + i)->distance > (start + i + 1)->distance)
        {
          return FALSE;
        }
    }
  return TRUE;
}

int is_equal (BusLine *start_sorted,
              BusLine *end_sorted, BusLine *start_original,
              BusLine *end_original)
{
  if (end_sorted - start_sorted != end_original - start_original)
    {
      return FALSE;
    }
  for (int i = 0; (start_original + i) < end_original; i++)
    {
      int equal = FALSE;
      for (int j = 0; (start_sorted + j) < end_sorted; j++)
        {
          if (((start_original + i)->line_number
               == (start_sorted + j)->line_number)
              && ((start_original + i)->duration
                  == (start_sorted + j)->duration)
              && ((start_original + i)->distance
                  == (start_sorted + j)->distance))
            {
              equal = TRUE;
            }
        }
      if (equal == FALSE)
        {
          return FALSE;
        }
    }
  return TRUE;
}

int is_sorted_by_duration (BusLine *start, BusLine *end)
{
  quick_sort (start, end);
  for (int i = 0; start + i < (end - 1); i++)
    {
      if ((start + i)->duration > (start + i + 1)->duration)
        {
          return FALSE;
        }
    }
  return TRUE;
}

