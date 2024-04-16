/*******************************************************************************
 * Name : waterjugpuzzle.cpp
 * Author : Aya Salama and Annanya Jain
 * Date : 10/21/2023
 * Description : Your goal is to write a program to solve the famous water jug puzzle using breadth-first search in C++.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <sstream>
#include <queue>
#include <vector>
using namespace std;

// Struct to represent state of water in the jugs.
struct State
{
    int a, b, c;
    string directions;
    State *parent;

    State(int _a, int _b, int _c, string _directions) : a{_a}, b{_b}, c{_c}, directions{_directions}, parent{nullptr} {}

    // String representation of state in tuple form.
    string to_string()
    {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};

void bfs(State capacities, State goal)
{
    int rows = capacities.a + 1, cols = capacities.b + 1;
    bool **arr = new bool *[rows];
    for (int i = 0; i < rows; i++) // initialize 2D array.
    {
        arr[i] = new bool[cols];
        for (int j = 0; j < cols; j++)
        {
            arr[i][j] = false;
        }
    }
    queue<State *> checks;
    State *initial = new State(0, 0, capacities.c, "Initial state. ");
    checks.push(initial);
    State *s;
    State *current;
    vector<State *> v_s;       // vector containing all new State's of s
    vector<State *> v_current; // vector containing all new State's of current
    while (!checks.empty())
    {
        current = new State(checks.front()->a, checks.front()->b, checks.front()->c, checks.front()->directions);
        current->parent = checks.front()->parent;
        v_current.push_back(current);
        checks.pop();

        if (current->a == goal.a && current->b == goal.b && current->c == goal.c)
        {
            vector<State> parents;
            delete initial;
            while (current->parent != nullptr)
            {
                parents.push_back(*current);
                current = current->parent;
            }
            State initial(0, 0, capacities.c, "Initial state. ");
            cout << initial.directions << initial.to_string() << endl;
            for (int i = parents.size() - 1; i >= 0; i--)
                cout << parents[i].directions << parents[i].to_string() << endl;
            for (int i = 0; i < rows; i++)
                delete[] arr[i];
            delete[] arr;
            for (State *curr : v_current)
                delete curr;
            for (State *s : v_s)
                delete s;
            return;
        }

        if (arr[current->a][current->b])
            continue;

        arr[current->a][current->b] = true;

        // Pour from C to A
        if (current->c > 0 && current->a < capacities.a)
        {
            int pour_amount = min(current->c, capacities.a - current->a);
            string direction;
            if (pour_amount == 1)
                direction = "Pour " + to_string(pour_amount) + " gallon from C to A. ";
            else
                direction = "Pour " + to_string(pour_amount) + " gallons from C to A. ";
            s = new State(current->a + pour_amount, current->b, current->c - pour_amount, direction);
            s->parent = current;
            checks.push(s);
            v_s.push_back(s);
        }

        // Pour from B to A
        if (current->b > 0 && current->a < capacities.a)
        {
            int pour_amount = min(current->b, capacities.a - current->a);
            string direction;
            if (pour_amount == 1)
                direction = "Pour " + to_string(pour_amount) + " gallon from B to A. ";
            else
                direction = "Pour " + to_string(pour_amount) + " gallons from B to A. ";
            s = new State(current->a + pour_amount, current->b - pour_amount, current->c, direction);
            s->parent = current;
            checks.push(s);
            v_s.push_back(s);
        }

        // Pour from C to B
        if (current->c > 0 && current->b < capacities.b)
        {
            int pour_amount = min(current->c, capacities.b - current->b);
            string direction;
            if (pour_amount == 1)
                direction = "Pour " + to_string(pour_amount) + " gallon from C to B. ";
            else
                direction = "Pour " + to_string(pour_amount) + " gallons from C to B. ";
            s = new State(current->a, current->b + pour_amount, current->c - pour_amount, direction);
            s->parent = current;
            checks.push(s);
            v_s.push_back(s);
        }

        // Pour from A to B
        if (current->a > 0 && current->b < capacities.b)
        {
            int pour_amount = min(current->a, capacities.b - current->b);
            string direction;
            if (pour_amount == 1)
                direction = "Pour " + to_string(pour_amount) + " gallon from A to B. ";
            else
                direction = "Pour " + to_string(pour_amount) + " gallons from A to B. ";
            s = new State(current->a - pour_amount, current->b + pour_amount, current->c, direction);
            s->parent = current;
            checks.push(s);
            v_s.push_back(s);
        }

        // Pour from B to C
        if (current->b > 0 && current->c < capacities.c)
        {
            int pour_amount = min(current->b, capacities.c - current->c);
            string direction;
            if (pour_amount == 1)
                direction = "Pour " + to_string(pour_amount) + " gallon from B to C. ";
            else
                direction = "Pour " + to_string(pour_amount) + " gallons from B to C. ";
            s = new State(current->a, current->b - pour_amount, current->c + pour_amount, direction);
            s->parent = current;
            checks.push(s);
            v_s.push_back(s);
        }

        // Pour from A to C
        if (current->a > 0 && current->c < capacities.c)
        {
            int pour_amount = min(current->a, capacities.c - current->c);
            string direction;
            if (pour_amount == 1)
                direction = "Pour " + to_string(pour_amount) + " gallon from A to C. ";
            else
                direction = "Pour " + to_string(pour_amount) + " gallons from A to C. ";
            s = new State(current->a - pour_amount, current->b, current->c + pour_amount, direction);
            s->parent = current;
            checks.push(s);
            v_s.push_back(s);
        }
    }
    for (int i = 0; i < rows; i++)
        delete[] arr[i];
    delete[] arr;
    cout << "No solution.";
    delete initial;
    for (State *s : v_s)
        delete s;
    for (State *curr : v_current)
        delete curr;
}

int main(int argc, char **argv)
{
    if (argc != 7)
    {
        cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
        return 1;
    }
    int c1, c2, c3, g1, g2, g3;
    istringstream iss;
    iss.str(argv[1]);
    if (!(iss >> c1) || c1 <= 0)
    {
        cerr << "Error: Invalid capacity '" << argv[1] << "' for jug A." << endl;
        return 1;
    }
    iss.clear();
    iss.str(argv[2]);
    if (!(iss >> c2) || c2 <= 0)
    {
        cerr << "Error: Invalid capacity '" << argv[2] << "' for jug B." << endl;
        return 1;
    }
    iss.clear();
    iss.str(argv[3]);
    if (!(iss >> c3) || c3 <= 0)
    {
        cerr << "Error: Invalid capacity '" << argv[3] << "' for jug C." << endl;
        return 1;
    }
    iss.clear();
    iss.str(argv[4]);
    if (!(iss >> g1) || g1 < 0)
    {
        cerr << "Error: Invalid goal '" << argv[4] << "' for jug A." << endl;
        return 1;
    }
    iss.clear();
    iss.str(argv[5]);
    if (!(iss >> g2) || g2 < 0)
    {
        cerr << "Error: Invalid goal '" << argv[5] << "' for jug B." << endl;
        return 1;
    }
    iss.clear();
    iss.str(argv[6]);
    if (!(iss >> g3) || g3 < 0)
    {
        cerr << "Error: Invalid goal '" << argv[6] << "' for jug C." << endl;
        return 1;
    }
    if (g1 > c1)
    {
        cerr << "Error: Goal cannot exceed capacity of jug A." << endl;
        return 1;
    }
    if (g2 > c2)
    {
        cerr << "Error: Goal cannot exceed capacity of jug B." << endl;
        return 1;
    }
    if (g3 > c3)
    {
        cerr << "Error: Goal cannot exceed capacity of jug C." << endl;
        return 1;
    }
    if (g1 + g2 + g3 != c3)
    {
        cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
        return 1;
    }
    State capacities(c1, c2, c3, "Capacities");
    State goal(g1, g2, g3, "Goal");
    bfs(capacities, goal);
    return 0;
}