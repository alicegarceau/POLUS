import pixeliser_image
import input_UI
import UI
import Communication

input_UI.init_globales()

if __name__ == '__main__':
    if Communication.port_init() is True:
        data = [5, 5, 5, 5]
        Communication.msg_pixels(1, 2, 2, data)