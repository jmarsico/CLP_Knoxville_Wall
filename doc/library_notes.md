# Library meeting 4/29

## Admin Interface

Give the library staff abilities

Act
- pause wall for some amount of time (1 hour class)
- reboot

See
- check status (heartbeat, current scene, frame rate)
- see statistics (number of interactions)
- see canned API calls with labels

Long term
- Access ELK reporting stats

## Visitors Interface

Give library visitors ability to
- click a button to make the wall do something
- update parameters (windspeed, x, y)
- see a request URL being built
- see the different segments of the wall, labeled (teen room, outside, windows)

## API

Animations
- `POST /explode?start_x=0&start_y=30&size=50`
- `POST /sweep?start_x=0&start_y=0&end_x=100&end_y=100`
- `POST /dots?frequency=100&amount=3`
- `POST /force?type=wind&strength=100&direction=left`
- `POST /force?type=gravity&strength=93&direction=up`

Controls
- `GET /status`
- `POST /shutdown`
- `POST /restart`

## Todo
- Update invoice/estimate to include video feed
- Update invoice to include POST bodies
