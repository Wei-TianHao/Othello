import requests
import time

SERVER_IP = "http://127.0.0.1:5000/"
SESSION_ID = 7
TIME_SEC = 60

player = ''

def get_action(board,player="W"):
    '''
    your core code will be put here
    '''
    pass

def initialize_session():
    '''
    initialize the session with you session id
    '''
    ret = requests.get(SERVER_IP+"/create_session/"+SESSION_ID)
    if ret.text in ["W","B"]:
        player = ret.text
    else:
        print("unexpected error!")

def loop():
    # get board information in string format
    ret = requests.get(SERVER_IP+"/board_string/"+SESSION_ID)

    x,y= get_action(board,player)
    while(True):
        try:
            ret = requests.post(SERVER_IP+"/move/"+SESSION_ID+"/"+str(x)+"/"+str(y)+"/"+player)
            if ret.text == 'SUCCESS':
                break
            else:
                print('invalid move')
        except:
            print("unexpected error")
    return board

def is_your_turn():
    ret = requests.get(SERVER_IP+"/turn/"+SESSION_ID)
    return ret.text == player

def is_not_end(board):
    '''
    if the game has ended or not
    '''
    pass

def board_initialize():
    pass

if __name__ == "__main__":
    print("a sample code for reversi agent")


    initialize_session()
    board = board_initialize()
    while(is_not_end(board)):
        if(is_your_turn()):
            board=loop()
        else:
            time.sleep(TIME_SEC)
