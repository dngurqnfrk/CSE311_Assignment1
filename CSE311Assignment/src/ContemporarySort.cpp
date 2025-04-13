#include "ContemporarySort.h"

/* library Sort */
void librarySort::sort(std::vector<int> &arr) {
    if (arr.size() < 4) {
        basic_sort.sort(arr);
        return;
    }

    int height = ceil(log2(arr.size()) + 1);

    size = 1;
    max_size = pow(2, height);
    std::vector<int> gapped_arr(max_size);
    for (int i = 0; i < max_size; i++)
        gapped_arr[i] = gap;
    
    int index = 0;
    stage_ceil = 1;
    for (int i = 0; i < height; i++) {
        while (index < stage_ceil) {
            gapped_insert(gapped_arr, arr[index]);
            // std::cout << "(" << arr[index] << ") : "; // DEBUG
            // print_arr(gapped_arr, size); // DEBUG
            index++;
        }

        // std::cout << "In the stage " << i << " Gapped Array : "; // DEBUG
        if (index < arr.size())
            rearrange(gapped_arr);

        size = pow(2, i + 1);
    
        if(size > max_size)
            size = max_size;

        //<DEBUG>
        
        // print_arr(gapped_arr, size);
        
        //</DEBUG>

        stage_ceil += pow(2, i);
        if (stage_ceil >= arr.size())
            stage_ceil = arr.size();
    }

    index = 0;
    for (int i = 0; i < max_size; i++) {
        if(is_gap(gapped_arr[i]))
            continue;

        arr[index] = gapped_arr[i];
        index++;
    }
}

void librarySort::gapped_insert(std::vector<int> &arr, int value) {
    if (size < 2) {
        arr[0] = value;
        return;
    }

    int start = 0;
    int end = size / 2 - 1;

    while (start < end) {
        int mid = (start + end) / 2;

        if (arr[mid * 2 + 1] > value)
            end = mid - 1;
        else
            start = mid + 1;
    }

    int insert_index = start * 2 + 1;
    if (is_gap(arr[insert_index])) {
        arr[insert_index] = value;
        return;
    }

    if (arr[insert_index] > value && is_gap(arr[insert_index - 1])) {
        arr[insert_index - 1] = value;
        return;
    } else if (arr[insert_index] <= value && insert_index + 1 < max_size && is_gap(arr[insert_index + 1])) {
        if (is_gap(arr[insert_index + 2])) {
            arr[insert_index + 2] = value;
            size += 2;
            return;
        }

        arr[insert_index + 1] = value;
        if (insert_index + 1 == size)
            size++;
        return;
    } else if (arr[insert_index] <= value) {
        while (insert_index < size && arr[insert_index] <= value)
            insert_index++;
        
        if (insert_index >= max_size)
            insert_index = max_size - 1;
    } else {
        while (insert_index >= 0 && arr[insert_index] > value)
            insert_index--;
        
        insert_index++;
    }

    int gap_index = find_gap(arr, insert_index);
    arr[gap_index] = value;
    
    if (insert_index < gap_index) {
        for (int i = gap_index; i > insert_index; i--)
            swap(arr, i-1, i);
    } else {
        insert_index--;
        for (int i = gap_index; i < insert_index; i++)
            swap(arr, i, i+1);
    }
}

int librarySort::find_gap(std::vector<int> &arr, int pivot_index) {
    int right = pivot_index + 1;
    int left = pivot_index - 1;
    while (true) {
        if (right < size && is_gap(arr[right]))
            return right;
        if (left >= 0 && is_gap(arr[left]))
            return left;

        if (right < size)
            right++;
        if (left > 0)
            left--;

        if (right == size - 1 && left == 0)
            throw std::runtime_error("Error : (librarySort::find_gap) can't find gap.\n");
    }
}

void librarySort::rearrange(std::vector<int> &arr) {
    std::vector<int> temp_arr;
    int i = 0;
    int j = 0;
    while(j < stage_ceil) {
        if(!is_gap(arr[i])) {
            temp_arr.emplace_back(arr[i]);
            arr[i] = gap;
            j++;
        }
        i++;
    }

    // DEBUG
    bool is_sorted = true;
    for (int i = 1; i < temp_arr.size(); i++) {
        if (temp_arr[i - 1] > temp_arr[i])
            is_sorted = false;
    }

    if(!is_sorted)
        std::cout <<"NOT SORTED:<\n";
    // /DEBUG
    
    if (2 * temp_arr.size() - 1 > arr.size()) {
        std::cout << "<DEBUG>" << std::endl;
        std::cout << "arr : " << arr.size() << std::endl;
        print_arr(arr, arr.size());
        std::cout << "temp_arr : " << temp_arr.size() << std::endl;
        print_arr(temp_arr, temp_arr.size());
        std::cout << "</DEBUG>" << std::endl;
        throw std::runtime_error("Error : (librarySort::rearrange) what is wrong.\n");
    }

    for(int i = 0; i < temp_arr.size(); i++) {
        arr[2*i + 1] = temp_arr[i];
    }
}

/* test_timSort
   This is just basic mixture of binary insertion sort and merge sort */
void test_timSort::sort(std::vector<int> &arr) {
    if (arr.size() < 2)
        return;

    tim_sort(arr, 0, arr.size() - 1);
}

void test_timSort::tim_sort(std::vector<int> &arr, int start, int end) {
    if (start >= end)
        return;

    if (end - start < k) {
        insertion_sort(arr, start, end);
        // DEBUG
        /*
        std::cout << "insertionSort is occured (" << start << ", " << end << ") : ";
        for (int i = start; i <= end; i++)
            std::cout << arr[i] << " ";
        std::cout << std::endl;
        */
        // /DEBUG
        return;
    }

    int mid = (start + end) / 2;
    tim_sort(arr, start, mid);
    tim_sort(arr, mid + 1, end);
    merge_sort.merge(arr, start, mid, end);
}

void test_timSort::insertion_sort(std::vector<int> &arr, int start, int end) {
    for (int i = start + 1; i <= end; i++) {
        int s = start;
        int e = i - 1;

        while (s < e) {
            int mid = (s + e) / 2;
            if (arr[mid] > arr[i])
                e = mid - 1;
            else if (arr[mid] < arr[i])
                s = mid + 1;
            else {
                s = mid + 1;
                break;
            }
        }

        if (arr[s] < arr[i])
            s++;

        for (int j = i; j > s; j--) {
            swap(arr, j-1, j);
        }
    }
}

/* timSort
   this is the real version of timSort by Tim Peters */

void timSort::sort(std::vector<int> &arr) {
    if (arr.size() < 2)
        return;

    probe_run(arr);

    // <DEBUG>
    /*
    std::cout << "run arr : ";
    for (int i = 0; i < run_arr.size(); i++) {
        std::cout << run_arr[i] << " ";
    }
    std::cout << "\n";
    */
    // </DEBUG>
    run_height = 0;
    stack_start = run_arr.size() - 1;
    int start = 0;
    for(int i = 0; i < run_arr.size(); i++) {
        if (stack_start > 0) {
            stack_start--;
            run_height++;
        }
        else
            break;
        merge_collapse(arr);

        // <DEBUG>
        /*
        std::cout << "run_arr (" << i << ", H = " << run_height << ") : ";
        for (int i = stack_start; i <= stack_start + run_height; i++)
            std::cout << run_arr[i] << " ";
        std::cout << std::endl;
        */
        // </DEBUG>
    }

    if (run_height != 1)
        merge_force_collapse(arr);

    run_arr.clear();
}

void timSort::probe_run(std::vector<int> &arr) {
    int i = 1;
    int back_index = 0;
    bool descending = arr[i - 1] > arr[i];
    run_arr.emplace_back(0);
    while (i < arr.size()) {
        if (descending && arr[i - 1] < arr[i]) {
            if (i + 1 < arr.size())
                descending = arr[i] > arr[i + 1];
            reverse_arr(arr, back_index, i - 1);
            run_arr.emplace_back(i);
            back_index = i;
        } else if(!descending && arr[i - 1] > arr[i]) {
            if (i + 1 < arr.size())
                descending = arr[i] > arr[i + 1];
            run_arr.emplace_back(i);
            back_index = i;
        }
        i++;
    }

    if (descending)
        reverse_arr(arr, back_index, arr.size() - 1);

    run_arr.emplace_back(arr.size());
    reverse_arr(run_arr, 0, run_arr.size() - 1);
}

void timSort::merge_collapse(std::vector<int> &arr) {
    while (run_height > 1) {
        int n = run_height - 2;
        
        int R_arr[5];
        R_arr[1] = run_arr[stack_start] - run_arr[stack_start + 1];
        R_arr[2] = run_arr[stack_start + 1] - run_arr[stack_start + 2];
        if (n > 0)
            R_arr[3] = run_arr[stack_start + 2] - run_arr[stack_start + 3];
        if (n > 1)
            R_arr[4] = run_arr[stack_start + 3] - run_arr[stack_start + 4];

        if ((n > 0 && R_arr[3] <= R_arr[1] + R_arr[2]) || 
            (n > 1 && R_arr[4] <= R_arr[2] + R_arr[3])) {
            // (n > 0 && R3 <= R2 + R1) || (n > 1 && R4 <= R3 + R2)
            if (R_arr[3] < R_arr[1]) {
                // std::cout << "R2 and R3 merged : " << run_arr[stack_start + 3] << " " << run_arr[stack_start + 2] - 1 << " "
                //          << run_arr[stack_start + 1] - 1 << std::endl;
                // R3 < R1 then merge R2 and R3
                merge_sort.merge(arr, run_arr[stack_start + 3], run_arr[stack_start + 2] - 1,
                                 run_arr[stack_start + 1] - 1);
                for(int i = stack_start + 3; i <= stack_start + run_height; i++)
                    swap(run_arr, i - 1, i);
            } else {
                // else then merge R1 and R2
                //std::cout << "R1 and R2 merged : " << run_arr[stack_start + 2] << " " << run_arr[stack_start + 1] - 1 << " "
                //          << run_arr[stack_start] - 1 << std::endl;
                merge_sort.merge(arr, run_arr[stack_start + 2], run_arr[stack_start + 1] - 1,
                                 run_arr[stack_start] - 1);
                for(int i = stack_start + 2; i <= stack_start + run_height; i++)
                    swap(run_arr, i - 1, i);
            }
        } else if (R_arr[2] < R_arr[1]) {
            // R2 < R1 then merge R1 and R2
            //std::cout << "R1 and R2 merged : " << run_arr[stack_start + 2] << " " << run_arr[stack_start + 1] - 1 << " "
            //          << run_arr[stack_start] - 1 << std::endl;
            merge_sort.merge(arr, run_arr[stack_start + 2], run_arr[stack_start + 1] - 1,
                             run_arr[stack_start] - 1);
            for(int i = stack_start + 2; i <= stack_start + run_height; i++)
                swap(run_arr, i - 1, i);
        } else
            break;

        run_height--;
    }
}

void timSort::merge_force_collapse(std::vector<int> &arr) {
    while (run_height > 1) {
        // std::cout << "R1 and R2 merged : " << run_arr[stack_start + 2] << " " << run_arr[stack_start + 1] - 1 << " "
        //          << run_arr[stack_start] - 1 << std::endl;
        merge_sort.merge(arr, run_arr[stack_start + 2], run_arr[stack_start + 1] - 1,
            run_arr[stack_start] - 1);
        for(int i = stack_start + 2; i <= stack_start + run_height; i++)
            swap(run_arr, i - 1, i);

        run_height--;

        // <DEBUG>
        /*
        std::cout << "run_arr (H = " << run_height << ") : ";
        for (int i = stack_start; i <= stack_start + run_height; i++)
            std::cout << run_arr[i] << " ";
        std::cout << std::endl;
        // </DEBUG>
        */
    }
}

/* Cocktail Shacker Sort */
void cocktailShakerSort::sort(std::vector<int> &arr) {
    if (arr.size() < 2)
        return;

    int start = 0;
    int end = arr.size() - 1;
    bool descend = false;

    while (start < end) {
        if (!descend) {
            int not_swapped_index = start;
            for(int i = start + 1; i <= end; i++) {
                if (arr[i - 1] > arr[i]) {
                    swap(arr, i-1, i);
                    not_swapped_index = i;
                }
            }
            
            descend = true;
            end = not_swapped_index - 1;
        } else {
            int not_swapped_index = end - 1;
            for (int i = end - 1; i >= start; i--) {
                if (arr[i] > arr[i + 1]) {
                    swap(arr, i, i+1);
                    not_swapped_index = i;
                }
            }

            descend = false;
            start = not_swapped_index + 1;
        }
    }
}

/* combSort */
void combSort::sort(std::vector<int> &arr) {
    if (arr.size() < 2)
        return;

    int gap = arr.size() / 2;
    while (gap > 1) {
        gaps.emplace_back(gap);
        gap *= 0.75;
    }

    for (int increment : gaps)
        gapped_bubble_sort(arr, increment);

    bubble_sort.sort(arr);

    gaps.clear();
}

void combSort::gapped_bubble_sort(std::vector<int> &arr, int gap) {
    for(int i = 0; i < arr.size() - gap; i++) {
        if (arr[i] > arr[i + gap])
            swap(arr, i, i + gap);
    }
}

/* tournamentSort */
void tournamentSort::sort(std::vector<int> &arr) {
    if (arr.size() < 2)
        return;

    std::list<tournamentTree*> tree_list = listify(arr);

    tournament(tree_list);
    tournamentTree* root = tree_list.front();

    int i = 0;
    while(!root->children.empty()) {
        arr[i] = root->key;
        tree_list = root->children;
        tournament(tree_list);
        root = tree_list.front();
        i++;
    }
    arr[i] = root->key;
}

std::list<tournamentTree*> tournamentSort::listify(std::vector<int> &arr) {
    std::list<tournamentTree*> tree_list;
    for(int i = 0; i < arr.size(); i++)
        tree_list.emplace_back(new tournamentTree(arr[i]));

    return tree_list;
}

tournamentTree* tournamentSort::tournament_play(tournamentTree* X, tournamentTree* Y) {
    if (X->key <= Y->key) {
        X->insert_child(Y);
        return X;
    } else {
        Y->insert_child(X);
        return Y;
    }
}

void tournamentSort::tournament(std::list<tournamentTree*> &tree_list) {
    while(tree_list.size() > 1) {
        int list_iter = tree_list.size() / 2;

        for(int i = 0; i < list_iter; i++) {
            tournamentTree* X = tree_list.front();
            tree_list.pop_front();
            tournamentTree* Y = tree_list.front();
            tree_list.pop_front();
            tree_list.push_back(tournament_play(X, Y));
        }
    }

    // tree_list.front()->print_tree(tree_list.front(), 0);
}

tournamentTree::tournamentTree(int key_) 
: key(key_)
{
    parent = nullptr;
}

void tournamentTree::insert_child(tournamentTree* child) {
    this->children.emplace_front(child);
}

void tournamentTree::print_tree(tournamentTree* root, int height) {
    for (int i = 0; i < height - 1; i++)
        std::cout << "    ";

    if (height > 0)
        std::cout << "+--";

    std::cout << root->key << "\n";

    for (auto child : root->children)
        print_tree(child, height + 1);
}

/* introSort */
void introSort::sort(std::vector<int> &arr) {
    intro_sort(arr, 0, arr.size() - 1, floor(log2(arr.size())));

    // basic_sort.sort(arr); // Why use InsertionSort?
}

void introSort::intro_sort(std::vector<int> &arr, int start, int end, int depth_limit) {
    if (start >= end)
        return;

    if (depth_limit <= 0) {
        heap_sort.heap_index_sort(arr, start, end);
        return;
    }

    int mid = quick_sort.partition(arr, start, end);
    intro_sort(arr, start, mid - 1, depth_limit - 1);
    intro_sort(arr, mid + 1, end, depth_limit - 1);
}