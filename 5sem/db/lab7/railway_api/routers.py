from fastapi import APIRouter, Depends
from sqlalchemy.ext.asyncio import AsyncSession
from sqlalchemy import select, func, extract, case, text
from typing import List
from database import get_db
from models import Train, Route, Schedule, Car, Seat, Ticket
from schemas import (
    TicketByTrainTypeSchema,
    AvgPriceByRouteSchema,
    SeatsByCarTypeSchema,
    PopularRouteSeasonSchema,
    TrainRatingByCarTypeSchema,
    TrainFromAToBSchema,
)

router = APIRouter(prefix="/api", tags=["Железнодорожные запросы"])


@router.get("/tickets-by-train-type", response_model=List[TicketByTrainTypeSchema])
async def tickets_by_train_type(db: AsyncSession = Depends(get_db)):
    query = (
        select(Train.traintype, func.count(Ticket.id).label("total_tickets"))
        .join(Schedule, Train.id == Schedule.trainid)
        .join(Car, Schedule.id == Car.scheduleid)
        .join(Seat, Car.id == Seat.carid)
        .join(Ticket, Seat.id == Ticket.seatid)
        .group_by(Train.traintype)
    )
    result = await db.execute(query)
    return [
        TicketByTrainTypeSchema(train_type=r[0], total_tickets=r[1])
        for r in result.all()
    ]


@router.get("/avg-price-by-route", response_model=List[AvgPriceByRouteSchema])
async def avg_price_by_route(db: AsyncSession = Depends(get_db)):
    query = (
        select(
            Route.departurestation,
            Route.arrivalstation,
            func.round(func.avg(Ticket.price), 2).label("avg_price"),
        )
        .join(Schedule, Route.id == Schedule.routeid)
        .join(Car, Schedule.id == Car.scheduleid)
        .join(Seat, Car.id == Seat.carid)
        .join(Ticket, Seat.id == Ticket.seatid)
        .group_by(Route.departurestation, Route.arrivalstation)
    )
    result = await db.execute(query)
    return [
        AvgPriceByRouteSchema(
            departure_station=r[0], arrival_station=r[1], average_price=r[2]
        )
        for r in result.all()
    ]


@router.get("/seats-by-car-type", response_model=List[SeatsByCarTypeSchema])
async def seats_by_car_type(db: AsyncSession = Depends(get_db)):
    query = select(Car.cartype, func.sum(Car.totalseats)).group_by(Car.cartype)
    result = await db.execute(query)
    return [SeatsByCarTypeSchema(car_type=r[0], total_seats=r[1]) for r in result.all()]


@router.get("/popular-routes-by-season", response_model=List[PopularRouteSeasonSchema])
async def popular_routes_by_season(db: AsyncSession = Depends(get_db)):
    season = case(
        (extract("month", Schedule.departuredatetime).in_([12, 1, 2]), "зима"),
        (extract("month", Schedule.departuredatetime).in_([3, 4, 5]), "весна"),
        (extract("month", Schedule.departuredatetime).in_([6, 7, 8]), "лето"),
        else_="осень",
    ).label("season")

    query = (
        select(
            season, Route.departurestation, Route.arrivalstation, func.count(Ticket.id)
        )
        .join(Seat, Ticket.seatid == Seat.id)
        .join(Car, Seat.carid == Car.id)
        .join(Schedule, Car.scheduleid == Schedule.id)
        .join(Route, Schedule.routeid == Route.id)
        .group_by(season, Route.departurestation, Route.arrivalstation)
        .order_by(season, func.count(Ticket.id).desc())
    )
    result = await db.execute(query)
    return [
        PopularRouteSeasonSchema(
            season=r[0], departure_station=r[1], arrival_station=r[2], passengers=r[3]
        )
        for r in result.all()
    ]


@router.get(
    "/train-rating-by-car-type", response_model=List[TrainRatingByCarTypeSchema]
)
async def train_rating_by_car_type(db: AsyncSession = Depends(get_db)):
    query = (
        select(Train.trainnumber, Train.traintype, Car.cartype, func.count(Ticket.id))
        .join(Schedule, Train.id == Schedule.trainid)
        .join(Car, Schedule.id == Car.scheduleid)
        .join(Seat, Car.id == Seat.carid)
        .join(Ticket, Seat.id == Ticket.seatid)
        .group_by(Train.trainnumber, Train.traintype, Car.cartype)
        .order_by(Car.cartype, func.count(Ticket.id).desc())
    )
    result = await db.execute(query)
    return [
        TrainRatingByCarTypeSchema(
            train_number=r[0], train_type=r[1], car_type=r[2], sold_tickets=r[3]
        )
        for r in result.all()
    ]


@router.get("/trains-from-a-to-b", response_model=List[TrainFromAToBSchema])
async def trains_from_a_to_b(
    departure: str, arrival: str, db: AsyncSession = Depends(get_db)
):
    query = text("SELECT * FROM get_trains_from_a_to_b(:dep, :arr)")
    result = await db.execute(query, {"dep": departure, "arr": arrival})
    rows = result.fetchall()
    return [
        TrainFromAToBSchema(
            train_number=row[0], train_type=row[1], departure=row[2], arrival=row[3]
        )
        for row in rows
    ]
