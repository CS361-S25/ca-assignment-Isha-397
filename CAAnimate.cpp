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


    //some vectors to hold information about the CA
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


        //showing how to set a cell to 'alive'
        // cells[0][0] = 1;
        // cells[1][0] = 1;
        // cells[2][1] = 1;
        // cells[0][2] = 1;
        // cells[1][2] = 1;
        // cells[2][2] = 1;
        // cells[6][5] = 1;

        AddGlider(1, 1);

    }

    void AddGlider(int x_offset, int y_offset) {
        cells[(x_offset + 1) % num_w_boxes][(y_offset + 0) % num_h_boxes] = 1;
        cells[(x_offset + 2) % num_w_boxes][(y_offset + 1) % num_h_boxes] = 1;
        cells[(x_offset + 0) % num_w_boxes][(y_offset + 2) % num_h_boxes] = 1;
        cells[(x_offset + 1) % num_w_boxes][(y_offset + 2) % num_h_boxes] = 1;
        cells[(x_offset + 2) % num_w_boxes][(y_offset + 2) % num_h_boxes] = 1;
    }


    int GetNeighborValue(int x, int y) {
        // int wrapped_x = (x + num_w_boxes) % num_w_boxes;
        // int wrapped_y = (y + num_h_boxes) % num_h_boxes;
        // return cells[wrapped_x][wrapped_y];
        int count = 0;
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0) continue;
                int nx = (x + dx + num_w_boxes) % num_w_boxes;
                int ny = (y + dy + num_h_boxes) % num_h_boxes;
                count += cells[nx][ny];
            }
        }
        return count;
    }

    void UpdateCells() {
        // std::vector<std::vector<int>> new_cells = cells;

        for (int x = 0; x < num_w_boxes; ++x) {
            for (int y = 0; y < num_h_boxes; ++y) {
                int neighbors = GetNeighborValue(x, y);
                // int alive_neighbors = 0;

                // for (int dx = -1; dx <= 1; ++dx) {
                //     for (int dy = -1; dy <= 1; ++dy) {
                //         if (dx == 0 && dy == 0) continue;
                //         alive_neighbors += GetNeighborValue(x + dx, y + dy);
                //     }
                // }

                if (cells[x][y] == 1) {
                    next_cells[x][y] = (neighbors == 2 || neighbors == 3) ? 1 : 0;
                } else {
                    next_cells[x][y] = (neighbors == 3) ? 1 : 0;
                }
            }
        }

        cells = next_cells;
    }

    void DoFrame() override {
        canvas.Clear();

        for (int x = 0; x < num_w_boxes; x++){
             for (int y = 0; y < num_h_boxes; y++) {
                    std::string fill_color = cells[x][y] ? "black" : "white";
                    canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, fill_color, "black");
                // if (cells[x][y] == 0) {
                //     //Draw a rectangle on the canvas filled with white and outlined in black
                //     canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "white", "black");
                // } else {
                //     //Draw a rectangle filled with black
                //     canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "black", "black");
                // }
                
            }
        }

        //Place to update the values of all the cells based on CA rules
        UpdateCells();
    }
    
    

};

CAAnimator animator;

int main() {
    //Have animator call DoFrame once to start
    animator.Step();
}