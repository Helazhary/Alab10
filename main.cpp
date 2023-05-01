#include <bits/stdc++.h>
#include <sstream>
using namespace std;

// Split a sentence into individual words
vector<string> sentenceBreakdown(string input_sentence)
{
    vector<string> words;

    stringstream ss(input_sentence);
    string word;

    while (ss >> word)
    {
        words.push_back(word);
    }

    return words;
}

// Display wrapped text given pointers and words
void display_wrapped_text(vector<int> line_endings, vector<string> words)
{
    int start = 0;
    int end = 0;
    while (end <= line_endings.size() - 1)
    {
        // Get the ending position of the current line
        end = line_endings[end];
        // Print the current line
        for (int i = start; i < end; i++)
        {
            cout << words[i] << " ";
        }
        cout << endl;

        // Move on to the next line
        start = end;
        end++;
    }
}
// Calculate the optimal line breaks and their associated cost
pair<int, vector<int>> calculate_line_breaks(vector<vector<int>> cost_matrix)
{
    int n = cost_matrix.size();
    vector<int> min_cost(n, INT_MAX);
    vector<int> optimal_break(n, -1);

    // Compute the minimum cost of wrapping lines up to each position
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            if (cost_matrix[j][i] == -1)
            {
                continue;
            }

            int cost = (j == 0) ? cost_matrix[j][i] : min_cost[j - 1] + cost_matrix[j][i];
            if (cost < min_cost[i])
            {
                min_cost[i] = cost;
                optimal_break[i] = j;
            }
        }
    }

    // Correct the pointers based on optimal line breaks
    int pointer = n - 1;
    while (pointer >= 0)
    {
        int breakpoint = optimal_break[pointer];
        for (int i = breakpoint; i <= pointer; i++)
        {
            optimal_break[i] = pointer + 1;
        }
        pointer = breakpoint - 1;
    }

    // Return the minimum cost and optimal line break positions
    int total_cost = min_cost[min_cost.size() - 1];

    pair<int, vector<int>> result;
    result.first = total_cost;
    result.second = optimal_break;

    return result;
}

// Compute cost matrix for all possible line breaks
vector<vector<int>> calculate_cost_matrix(vector<string> words, int max_line_width)
{
    int n = words.size();
    vector<vector<int>> cost_matrix(n, vector<int>(n, -1));

    for (int i = 0; i < n; i++)
    {
        int current_line_length = words[i].size();
        int current_cost = pow(max_line_width - current_line_length, 2);
        cost_matrix[i][i] = current_cost;

        for (int j = i + 1; j < n; j++)
        {
            current_line_length += words[j].size() + 1;
            if (current_line_length > max_line_width)
            {
                break;
            }
            int current_cost = pow(max_line_width - current_line_length, 2);
            cost_matrix[i][j] = current_cost;
        }
    }

    return cost_matrix;
}

// Wrap given text to the specified line width and display the result
void wrap_text(string input_sentence, int max_line_width)
{
    auto words = sentenceBreakdown(input_sentence);
    auto cost_matrix = calculate_cost_matrix(words, max_line_width);
    auto line_endings = calculate_line_breaks(cost_matrix);
    cout << "Minimum wrapping cost: " << line_endings.first << endl;
    display_wrapped_text(line_endings.second, words);
}

int main()
{
    string input_text;
    int max_line_width;

    // Get user input and wrap the text
    for (int i = 0; i < 2; i++)
    {
        cout << "Enter the text to be wrapped: ";
        getline(cin, input_text);
        cout << "Enter the maximum line width: ";
        cin >> max_line_width;
        wrap_text(input_text, max_line_width);
    }
}
