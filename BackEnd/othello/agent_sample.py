import requests
import time
from subprocess import Popen, PIPE

SERVER_IP = "http://47.89.179.202:5000"
SESSION_ID = 7
TIME_SEC = 60

player = 'B'
version = "roxanne"


def get_action(board,player="W"):
    '''
    your core code will be put here
    '''
    p = Popen(['one_step'], shell=True, stdout=PIPE, stdin=PIPE)
    value = board + ' ' + player + ' ' + version
    #value = bytes(value, 'UTF-8')  # Needed in Python 3.
    p.stdin.write(value)
    p.stdin.flush()
    ret = p.stdout.readline()
    print("one_step ret: ",ret)
    xy = [int(s) for s in ret.split() if s.isdigit()]
    print("get action ", xy)
    return xy[0], xy[1]
def initialize_session():
    '''
    initialize the session with you session id
    '''
    ret = requests.get(SERVER_IP+"/create_session/"+str(SESSION_ID))
    if ret.text in ["W","B"]:
        player = ret.text
    else:
        print("unexpected error!")
    
    print("initialize session sucess")

def loop():
    # get board information in string format
    ret = requests.get(SERVER_IP+"/board_string/"+str(SESSION_ID))
    board = ret.text
    x,y= get_action(board,player)
    while(True):
        try:
            ret = requests.post(SERVER_IP+"/move/"+str(SESSION_ID)+"/"+str(x)+"/"+str(y)+"/"+player)
            if ret.text == 'SUCCESS':
                break
            else:
                print('invalid move')
        except:
            print("unexpected error")
    print("move sucess")
    return board

def is_your_turn():
    ret = requests.get(SERVER_IP+"/turn/"+str(SESSION_ID))
    print("turn ", ret.text)
    return ret.text == player

def is_not_end(board):
    '''
    if the game has ended or not
    '''
    if(board == ""):
        return True
    ret = os.popen('is_end '+board).read()
    print("is not end ", int(ret) == 0)
    return int(ret) == 0;

def board_initialize():
    return ""

if __name__ == "__main__":
    print("a sample code for reversi agent")


    initialize_session()
    board = board_initialize()
    while(is_not_end(board)):
        if(is_your_turn()):
            board=loop()
        else:
            time.sleep(TIME_SEC)
