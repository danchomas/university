from fastapi import FastAPI
from routers import router
import uvicorn

app = FastAPI(
    title="railway api",
    description="lab 7 Maslennikov",
)

app.include_router(router)


@app.get("/")
async def root():
    return {"code": 200, "message": "успех"}


if __name__ == "__main__":
    uvicorn.run("main:app", host="127.0.0.1", port=8000, reload=True)
