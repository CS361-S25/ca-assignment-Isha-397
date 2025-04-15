#include "emp/web/Animate.hpp"
#include "emp/web/web.hpp"

emp::web::Document doc{"target"};

class CAAnimator : public emp::web::Animate {

    // grid width and height
    const int num_h_boxes = 10;
    const int num_w_boxes = 15;
    const double RECT_SIDE = 25;
    const double width{num_w_boxes * RECT_SIDE};
    const double height{num_h_boxes * RECT_SIDE};


    //2D vectors to hold information about the current and next state of cells
    std::vector<std::vector<int> > cells;
    std::vector<std::vector<int>> next_cells;
            

    // where we'll draw
    emp::web::Canvas canvas{width, height, "canvas"};

    int frame_count = 0;

public:

    CAAnimator() {
        // shove canvas into the div
        // along with some control buttons
        doc << canvas;
        doc << GetToggleButton("Toggle");
        doc << GetStepButton("Step");

        //fill the vectors with 0 to start
        cells.resize(num_w_boxes, std::vector<int>(num_h_boxes, 0));
        next_cells.resize(num_w_boxes, std::vector<int>(num_h_boxes, 0));


        //Add an initial glider pattern
         AddGlider(1, 1);

    }

    // Add a classic "glider" pattern to the grid at a specific offset.
    void AddGlider(int x_offset, int y_offset) {
        cells[(x_offset + 1) % num_w_boxes][(y_offset + 0) % num_h_boxes] = 1;
        cells[(x_offset + 2) % num_w_boxes][(y_offset + 1) % num_h_boxes] = 1;
        cells[(x_offset + 0) % num_w_boxes][(y_offset + 2) % num_h_boxes] = 1;
        cells[(x_offset + 1) % num_w_boxes][(y_offset + 2) % num_h_boxes] = 1;
        cells[(x_offset + 2) % num_w_boxes][(y_offset + 2) % num_h_boxes] = 1;
    }

    // Count the number of alive neighbors around a cell (with toroidal wrapping)
    int GetNeighborValue(int x, int y) {
        int count = 0;
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0) continue; // Skip the cell itself
                int nx = (x + dx + num_w_boxes) % num_w_boxes;
                int ny = (y + dy + num_h_boxes) % num_h_boxes;
                count += cells[nx][ny];
            }
        }
        return count;
    }

    // Apply Game of Life rules to update cell states
    void UpdateCells() {
        for (int x = 0; x < num_w_boxes; ++x) {
            for (int y = 0; y < num_h_boxes; ++y) {
                int neighbors = GetNeighborValue(x, y);

                // Live cell rules
                if (cells[x][y] == 1) {
                    next_cells[x][y] = (neighbors == 2 || neighbors == 3) ? 1 : 0;
                } else {
                    // Dead cell becomes alive if exactly 3 neighbors are alive
                    next_cells[x][y] = (neighbors == 3) ? 1 : 0;
                }
            }
        }

        // Swap next state into current state
        cells = next_cells;
    }

    // Draw the frame and update the CA grid
    void DoFrame() override {
        canvas.Clear();

        // Draw each cell on the canvas
        for (int x = 0; x < num_w_boxes; x++){
             for (int y = 0; y < num_h_boxes; y++) {
                    std::string fill_color = cells[x][y] ? "black" : "white";
                    canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, fill_color, "black");
            }
        }

       // Update cells for the next frame
        UpdateCells();
    }
};

// Create an instance of the animator
CAAnimator animator;

int main() {
    //Have animator call DoFrame once to start
    animator.Step();
}