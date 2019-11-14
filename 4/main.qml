import QtQuick 2.5
import QtQuick.Window 2.2





Window {
    visible: true
    width: 400
    height: 400
    title: qsTr("Chess")
    function board_color(index)
    {
        var row = Math.floor(index/8)
        if (index !== 0)
        {
            if (((row) % 2))
                if ((index+1) % 2)
                    return "white"
                else
                    return "black"
            else
                if ((index+1) % 2)
                    return "black"
                else
                    return "white"
        }
        else {
            return "red"
        }
    }

function valid_step(dest_x, dest_y, src_x, src_y)
{

    var mx = []
    var my = []
    mx[0] = src_x + 2
    mx[1] = src_x + 2
    my[0] = src_y + 1
    my[1] = src_y - 1
    mx[2] = src_x - 2
    mx[3] = src_x - 2
    my[2] = src_y + 1
    my[3] = src_y - 1
    my[4] = src_y + 2
    my[5] = src_y + 2
    mx[4] = src_x + 1
    mx[5] = src_x - 1
    my[6] = src_y - 2
    my[7] = src_y - 2
    mx[6] = src_x + 1
    mx[7] = src_x - 1
    for(var i = 0; i < 8; i++)
    {
        if(mx[i] <= 0 || my[i] <= 0 || mx[i] > 8 || my[i] > 8)
            continue
        else
        {
            if(mx[i] === dest_x && my[i] === dest_y)
                return true
        }
    }
    return false
}

    Grid {
        id: board
        anchors.fill: parent
        rows: 8
        columns: 8
        Repeater {
            id: chess_board
            model: {
                var cells = []
                for(var i = 0; i < 64; i++)
                {
                    cells[i] = true

                }
                return cells
            }
                Rectangle
                {
                    id: cell
                    property int col: Math.floor(index/8) + 1
                    property int row: index % 8 + 1
                    property int vis: -1

                    width: 50
                    height: 50
                    color: {
                        board_color(index)
                    }
                    border.width: 1
                    border.color: {return "red" }
                    MouseArea
                    {
                        id: mousearea
                        width: 50
                        height: 50
                        visible: true
                        onClicked:
                        {

                            if(cell.vis == 1)
                                return
                            if(valid_step(cell.row, cell.col, knight.x/50 + 1, knight.y/50 + 1))
                            {
                                chess_board.itemAt(knight.x/50  + 8 * ( knight.y/50 )).color = "gray"
                                 chess_board.itemAt(knight.x/50  + 8 * ( knight.y/50 )).vis = 1
                                knight.step(cell.col, cell.row)
                                cell.color = "red"
                            }
                        }
                     }

                }
        }







    Image
    {
        x:board.x
        y:board.y
        id: knight
        source: "img/hrs.png"
        width: 50
        height: 50
        function step(x, y)
        {
            knight.x = board.x + (y - 1)*50
            knight.y = board.y + (x - 1) * 50
        }
    }
    }
}
