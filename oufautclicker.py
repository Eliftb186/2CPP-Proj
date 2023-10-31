import pyautogui

while True:
    x, y = pyautogui.position()
    print(f"Position de la souris : x={x}, y={y}")
    if x == 0 and y == 0:
        break
    
